/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:35:14 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/28 18:19:59 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
is directory
bash: ../: Is a directory
bash: ./: Is a directory
bash: /: Is a directory

bash: syntax error near unexpected token `;;'

bash: ./l: No such file or directory
bash: //kk: No such file or directory
 */

int is_directory(char *path) // 126
{
	int i;

	i = 0;
	while (path && path[i])
	{
		if (path[i] != '/' && path[i] != '.')
			return (0);
		i++;
	}
	return (1);
}

int access_command(char *path, char **name)
{
	int i;
	char *pathname;
	char **paths;

	i = 0;
	paths = ft_split(path, ':');
	if (!paths)
		return (0);
	while (paths[i])
	{
		pathname = str_joins(paths[i++], (*name), "/");
		if (access(pathname, F_OK) != -1)
		{
			free((*name));
			free_array(paths);
			(*name) = pathname;
			return (1);
		}
		free(pathname);
	}
	free_array(paths);
	return (0);
}

int handle_commands(t_shell *shell)
{
	int count;

	count = count_cmds(shell->cmds);
	if (count == 1)
	{
		exec_command(shell);
	}
	else if (count > 1)
	{
	}
	printf("nb_cmds: %d\n", count_cmds(shell->cmds));
	return 0;
}

int exec_command(t_shell *shell)
{
	int wstatus;
	pid_t cpid;

	if (is_builtin(shell->cmds->name))
		exec_builtin(shell, shell->cmds);
	else if (is_directory(shell->cmds->name))
		put_command_error(shell, shell->cmds->name, "is a directory", 126);
	else if (access_command(get_env(shell, "PATH"), &shell->cmds->name) == 0)
		put_command_error(shell, shell->cmds->name, "command not found", 127);
	else
	{
		cpid = fork();
		if (cpid == -1)
			perror("Error: fork() failed\n");
		else if (cpid == 0)
		{
			handle_redirect(shell->cmds);
			// print_cmds(shell->cmds);
			if (execve(shell->cmds->name, shell->cmds->args, shell->envs))
			{
				put_command_error(shell, shell->cmds->name, strerror(errno), errno);
			}
			free_shell(shell);
			exit(0);
		}
		waitpid(cpid, &wstatus, WUNTRACED);
		free_cmds(shell->cmds);
	}
	return (0);
}
