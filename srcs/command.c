/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:35:14 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/05 21:59:42 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_commands(t_shell *shell)
{
	int i;
	t_cmd *cmd;

	i = 0;
	cmd = shell->cmds;
	if (shell->num_cmds == 1)
		exec_single_command(shell, cmd);
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
	}
	save_exit_status(shell);
}

int exec_single_command(t_shell *shell, t_cmd *cmd)
{
	pid_t pid;
	int status;

	if (is_builtin_command(cmd->name))
		exec_builtin_command(shell, cmd);
	else if (is_directory(cmd->name))
		show_command_error(shell, cmd->name, "is a directory", 126);
	else if (is_file_not_found(cmd->name))
		show_command_error(shell, cmd->name, "not such file or directory", 127);
	else if (is_command_not_found(get_env(shell, "PATH"), &cmd->name))
		show_command_error(shell, cmd->name, "command not found", 127);
	else if (is_file_permission_denied(cmd->name))
		show_command_error(shell, cmd->name, "permission denied", 126);
	else
	{
		pid = fork();
		if (pid == -1)
			perror("Error: fork() failed\n");
		else if (pid == 0)
		{
			handle_redirect(shell->cmds);
			if (execve(shell->cmds->name, shell->cmds->args, shell->envs))
				show_command_error(shell, cmd->name, strerror(errno), errno);
			exit(shell->exit_status);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
	}
	return (0);
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
			handle_redirect(cmd);
		}

		// output
		if (num < shell->num_cmds - 1)
		{
			// printf("output -> %s pipe: [%d][1] std: 1\n", cmd->name, num);
			dup2(shell->pipes[num][1], 1);
		}
		else if (num == shell->num_cmds - 1) // last command
		{
			handle_redirect(cmd);
		}
		close_pipes(shell);
		if (is_builtin_command(cmd->name))
			exec_builtin_command(shell, cmd);
		else if (is_directory(cmd->name))
			show_command_error(shell, cmd->name, "is a directory", 126);
		else if (is_file_not_found(cmd->name))
			show_command_error(shell, cmd->name, "not such file or directory", 127);
		else if (is_command_not_found(get_env(shell, "PATH"), &cmd->name))
			show_command_error(shell, cmd->name, "command not found", 127);
		else if (is_file_permission_denied(cmd->name))
			show_command_error(shell, cmd->name, "permission denied", 126);
		else if (execve(cmd->name, cmd->args, shell->envs))
			show_command_error(shell, cmd->name, strerror(errno), errno);
		exit(shell->exit_status);
	}
}