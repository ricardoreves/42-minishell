/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:35:14 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/01 23:18:20 by rpinto-r         ###   ########.fr       */
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

int is_directory_command(char *path) // 126
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

void process_command(t_shell *shell, t_cmd *cmd, int num)
{
	shell->pids[num] = fork();
	if (shell->pids[num] < 0)
		perror("Error: fork() failed");
	else if (shell->pids[num] == 0) // Child
	{
		// input
		if (num > 0)
		{
			// printf("input -> %s pipe: [%d][0] std: 0\n", cmd->name, num - 1);
			dup2(shell->pipes[num - 1][0], 0);
		}
		else if (num == 0) // first command
		{
			// handle_redirect(cmd);
		}

		// output
		if (num < shell->num_cmds - 1)
		{
			// printf("output -> %s pipe: [%d][1] std: 1\n", cmd->name, num);
			dup2(shell->pipes[num][1], 1);
		}
		else if (num == shell->num_cmds - 1) // last command
		{
			// handle_redirect(cmd);
		}
		close_pipes(shell);
		if (is_builtin_command(cmd->name))
			exec_builtin_command(shell, cmd);
		else if (is_directory_command(cmd->name))
			put_command_error(shell, cmd->name, "is a directory", 126);
		else if (access_command(get_env(shell, "PATH"), &cmd->name) == 0)
			put_command_error(shell, cmd->name, "command not found", 127);
		else if (execve(cmd->name, cmd->args, shell->envs))
			put_command_error(shell, cmd->name, strerror(errno), errno);
		free_shell(shell);
		exit(0);
	}
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

void handle_commands(t_shell *shell)
{
	int i;
	t_cmd *cmd;

	i = 0;
	cmd = shell->cmds;
	if (cmd->next == 0 && is_builtin_command(cmd->name))
		exec_builtin_command(shell, cmd);
	else if (is_directory_command(cmd->name))
		put_command_error(shell, cmd->name, "is a directory", 126);
	else if (access_command(get_env(shell, "PATH"), &cmd->name) == 0)
		put_command_error(shell, cmd->name, "command not found", 127);
	else
	{
		create_pids(shell);
		create_pipes(shell);
		while (cmd)
		{
			process_command(shell, cmd, i);
			cmd = cmd->next;
			i++;
		}
		close_pipes(shell);
		wait_pids(shell);
		free_cmds(shell->cmds);
	}
}

/* unused */
int exec_single_command(t_shell *shell)
{
	int wstatus;
	pid_t pid;

	if (is_builtin_command(shell->cmds->name))
		exec_builtin_command(shell, shell->cmds);
	else if (is_directory_command(shell->cmds->name))
		put_command_error(shell, shell->cmds->name, "is a directory", 126);
	else if (access_command(get_env(shell, "PATH"), &shell->cmds->name) == 0)
		put_command_error(shell, shell->cmds->name, "command not found", 127);
	else
	{
		pid = fork();
		if (pid == -1)
			perror("Error: fork() failed\n");
		else if (pid == 0)
		{
			handle_redirect(shell->cmds);
			if (execve(shell->cmds->name, shell->cmds->args, shell->envs))
			{
				put_command_error(shell, shell->cmds->name, strerror(errno), errno);
			}
			free_shell(shell);
			exit(0);
		}
		waitpid(pid, &wstatus, WCONTINUED);
		free_cmds(shell->cmds);
	}
	return (0);
}
