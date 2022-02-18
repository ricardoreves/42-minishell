/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:35:14 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/12 15:58:48 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libparser.h"

int find_command(t_shell *shell, char *name, char **pathname)
{
	int i;
	char *path;
	char **paths;

	i = 0;
	path = get_env(shell, "PATH");
	if (!path)
		return (0);
	paths = ft_split(path, ':');
	if (!paths)
		return (0);
	while (paths[i])
	{
		(*pathname) = str_joinsep(paths[i++], name, "/");
		// printf("%d %s\n", access((*pathname), F_OK), *pathname);
		if (access((*pathname), F_OK) != -1)
		{
			free_array(paths);
			return (1);
		}
		free((*pathname));
	}
	free_array(paths);
	return (0);
}

int exec_command(t_shell *shell)
{
	int wstatus;
	pid_t cpid;
	char **args;
	char *pathname;
	
	pathname = 0;

	args = parse(shell->cmdline, ".config/parser/bash.conf");
	// args = eval_varenv_map(shell, ft_split(shell->cmdline, ' '));
	// args = ft_split(shell->cmdline, ' ');
	if (is_builtin(args))
	{
		exec_builtin(shell, args);
		free_array(args);
		return (1);
	}

	cpid = fork();
	if (cpid == -1)
	{
		perror("Error: fork() failed\n");
		exit(1);
	}
	else if (cpid == 0)
	{
		printf("Child\n");
		// printf("%d\n", access(args[0], R_OK));

		if (ft_strncmp(args[0], "/", 1) == 0)
			put_command_error(shell, args[0], "is a directory");
		else if (find_command(shell, args[0], &pathname) == 0)
			put_command_error(shell, args[0], "command not found");
		else if (execve(pathname, args, shell->envs))
		{
			// shell->error = errno;
			put_command_error(shell, args[0], strerror(errno));
		}

		if (pathname)
			free(pathname);
		free_array(args);
		free_array(shell->envs);
		exit(0);
	}
	else
	{
		// wait(&wstatus);
		waitpid(cpid, &wstatus, WUNTRACED);
		printf("Parent\n");
		free_array(args);
	}

	return (0);
}
