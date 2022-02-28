/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:35:14 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/28 04:19:13 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_shell(t_shell *shell)
{
	if (shell->cmds)
		free_cmds(shell->cmds);
	if (shell->envs)
		free_array(shell->envs);
	if (shell->config)
		free(shell->config);
}

int find_command(t_shell *shell, char **name)
{
	int i;
	char *path;
	char **paths;
	char *pathname;

	i = 0;
	path = get_env(shell, "PATH");
	if (!path)
		return (0);
	paths = ft_split(path, ':');
	if (!paths)
		return (0);
	while (paths[i])
	{
		pathname = str_joinsep(paths[i++], (*name), "/");
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
	int ret;

	if (is_builtin(shell->cmds->name))
		exec_builtin(shell, shell->cmds);
	// else if (str_compare(shell->cmds->name, "/") == 0 || str_compare(shell->cmds->name, "./") == 0)
	// 	put_command_error(shell, shell->cmds->name, "is a directory");
	// else if (ft_strncmp(shell->cmds->name, "/", 1) || find_command(shell, &shell->cmds->name) == 0)
	//	put_command_error(shell, shell->cmds->name, "command not found");
	else
	{
		cpid = fork();
		if (cpid == -1)
			perror("Error: fork() failed\n");
		else if (cpid == 0)
		{
			handle_redirect(shell->cmds);
			// print_cmds(shell->cmds);
			ret = execve(shell->cmds->name, shell->cmds->args, shell->envs);
			if (errno == 2) // 127
				put_command_error(shell, shell->cmds->name, "command not found");
			else if (ret != 0)
			{
				shell->error = errno;
				printf("errno: %d\n", errno);
				put_command_error(shell, shell->cmds->name, strerror(errno));
			}
			free_shell(shell);
			exit(0);
		}
		waitpid(cpid, &wstatus, WUNTRACED);
		free_cmds(shell->cmds);
	}
	return (0);
}
