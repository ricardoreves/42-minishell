/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:35:14 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/28 22:35:41 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void close_pipes(t_shell *shell)
{
	int i;

	i = shell->num_pipes;
	while (i--)
	{
		if (close(shell->pipes[i][0]) != 0 || close(shell->pipes[i][1]) != 0)
			perror("Error: pipe close() failed");
	}
}

int create_pipes(t_shell *shell)
{
	int i;

	i = 0;
	shell->num_pipes = shell->num_cmds - 1;
	shell->pipes = (int **)ft_calloc(sizeof(int *), shell->num_pipes);
	if (!shell->pipes)
		return (0);
	i = 0;
	while (i < shell->num_pipes)
	{
		shell->pipes[i] = (int *)ft_calloc(sizeof(int), 2);
		if (pipe(shell->pipes[i]) != 0)
		{
			perror("Error: pipe() failed");
			return (0);
		}
		i++;
	}
	return (1);
}

void child_process_command(t_shell *shell, t_cmd *cmd, int idx)
{
	pid_t cpid;
	// int wstatus;

	cpid = fork();
	if (cpid < 0) // Error
	{
		perror("Error: fork() failed");
	}
	else if (cpid == 0) // Child
	{
		// input
		if (idx > 0)
		{
			dup2(shell->pipes[idx - 1][0], 0);
		}
		else if (idx == 0) // first
		{
			handle_redirect(cmd);
		}

		// output
		if (idx < shell->num_cmds - 1)
		{
			dup2(shell->pipes[idx][1], 1);
		}
		else if (idx == shell->num_cmds - 1) // last
		{
			handle_redirect(cmd);
		}
		close_pipes(shell);
		if (access_command(get_env(shell, "PATH"), &cmd->name) == 0)
		{
			put_command_error(shell, cmd->name, "command not found", 127);
		}
		else if (execve(cmd->name, cmd->args, shell->envs))
		{
			put_command_error(shell, cmd->name, strerror(errno), errno);
		}
		free_shell(shell);
		exit(0);
	}
	else // Parent
	{
		// waitpid(cpid, &wstatus, WCONTINUED);
		printf("cpid %d = %d\n", idx, cpid);
	}
}

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

void handle_commands(t_shell *shell)
{
	int i;
	t_cmd *cmd;
	int wstatus;

	if (shell->num_cmds == 1)
	{
		if (shell->cmds->name)
			exec_command(shell);
	}
	else if (shell->num_cmds > 1)
	{
		// print_cmds(shell->cmds);
		i = 0;
		cmd = shell->cmds;
		create_pipes(shell);
		while (cmd)
		{
			child_process_command(shell, cmd, i);
			cmd = cmd->next;
			i++;
		}
		close_pipes(shell);
		waitpid(-1, &wstatus, WCONTINUED);
		free_cmds(shell->cmds);
	}
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
			if (execve(shell->cmds->name, shell->cmds->args, shell->envs))
			{
				put_command_error(shell, shell->cmds->name, strerror(errno), errno);
			}
			free_shell(shell);
			exit(0);
		}
		waitpid(cpid, &wstatus, WCONTINUED);
		free_cmds(shell->cmds);
	}
	return (0);
}
