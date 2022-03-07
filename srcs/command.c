/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:35:14 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/07 19:07:25 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_commands(t_shell *shell)
{
	int		i;
	t_cmd	*cmd;

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
			if (!cmd->name)
				scan_stdin(cmd);
			process_command(shell, cmd, i);
			cmd = cmd->next;
			i++;
		}
		close_pipes(shell);
		wait_pids(shell);
	}
	save_exit_status(shell);
}

int	is_invalid_command(t_shell *shell, t_cmd *cmd)
{
	if (is_directory(cmd->name))
		show_command_error(shell, cmd->name, MSG_IS_DIRECTORY, 126);
	else if (is_file_not_found(cmd->name))
		show_command_error(shell, cmd->name, MSG_FILE_NOT_FOUND, 127);
	else if (is_command_not_found(get_env(shell, "PATH"), &cmd->name, 0))
		show_command_error(shell, cmd->name, MSG_COMMAND_NOT_FOUND, 127);
	else if (is_file_permission_denied(cmd->name))
		show_command_error(shell, cmd->name, MSG_PERMISSION_DENIED, 126);
	return (shell->exit_status);
}

int	exec_single_command(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	if (is_builtin_command(cmd))
		exec_builtin_command(shell, cmd);
	else if (is_invalid_command(shell, cmd) == 0)
	{
		pid = fork();
		if (pid == -1)
			perror("Error: fork() failed\n");
		else if (pid == 0)
		{
			handle_redirect_file(cmd);
			if (execve(cmd->name, cmd->args, shell->envs))
				show_command_error(shell, cmd->name, strerror(errno), errno);
			exit(shell->exit_status);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
	}
	return (0);
}

void	process_command(t_shell *shell, t_cmd *cmd, int num)
{
	shell->pids[num] = fork();
	if (shell->pids[num] < 0)
		perror("Error: fork() failed");
	else if (shell->pids[num] == 0)
	{
		redirect_input(shell, cmd, num);
		redirect_output(shell, cmd, num);
		close_pipes(shell);
		if (is_builtin_command(cmd))
			exec_builtin_command(shell, cmd);
		else if (is_invalid_command(shell, cmd) == 0)
		{
			if (execve(cmd->name, cmd->args, shell->envs))
				show_command_error(shell, cmd->name, strerror(errno), errno);
		}
		exit(shell->exit_status);
	}
}
