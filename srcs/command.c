/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:35:14 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/08 16:24:37 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_command(t_shell *shell, char *name, char **pathname)
{
	int i;
	char *path;
	char **paths;
	int ret;

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

	cpid = fork();
	if (cpid == 0)
	{
		args = eval_varenv_map(shell, ft_split(shell->cmdline, ' '));
		printf("Child\n");

		// printf("%d\n", access(args[0], R_OK));
		if (is_builtin(args))
			exec_builtin(shell, args);
		else if (ft_strncmp(args[0], "/", 1) == 0)
			put_command_error(shell, args[0], "is a directory");
		else if (find_command(shell, args[0], &pathname) == 0)
			put_command_error(shell, args[0], "command not found");
		else if (execve(pathname, args, shell->envs))
		{
			shell->error = errno;
			put_command_error(shell, args[0], strerror(errno));
		}
			
		// if (pathname)
		//	free(pathname);
		free_array(args);
		exit(0);
	}
	if (cpid > 0)
	{
		// wait(&wstatus);
		waitpid(cpid, &wstatus, WUNTRACED);
		printf("Parent\n");
		if (ft_strncmp(shell->cmdline, "exit", 4) == 0)
		{
			free_array(shell->envs);
			exit(0);
		}
	}
	if (cpid < 0)
	{
		perror("Error: fork() failed\n");
	}
	return (0);
}
