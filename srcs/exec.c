/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:35:14 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/12 01:22:13 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief execute toutes les commandes se trouvant dans shell->cmds
 * 
 * @param shell 
 */
void	exec_commands(t_shell *shell)
{
	int		i;
	t_cmd	*cmd;

	i = -1;
	prepare_here_doc_cmd(shell);
	cmd = shell->cmds;
	if (shell->num_cmds == 1)
		exec_single_command(shell, cmd);
	else
	{
		create_pids(shell);
		create_pipes(shell);
		while (cmd)
		{
			exec_child_command(shell, cmd, ++i);
			cmd = cmd->next;
		}
		close_pipes(shell);
		wait_pids(shell);
	}
	save_exit_status(shell);
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
			handle_redirect_file(shell, cmd);
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

void	exec_child_command(t_shell *shell, t_cmd *cmd, int num)
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

void	exec_builtin_command(t_shell *shell, t_cmd *cmd)
{
	if (str_compare(cmd->name, "cd") == 0)
		exec_cd(shell, cmd);
	else if (str_compare(cmd->name, "echo") == 0)
		exec_echo(shell, cmd);
	else if (str_compare(cmd->name, "env") == 0)
		exec_env(shell);
	else if (str_compare(cmd->name, "exit") == 0)
		exec_exit(shell);
	else if (str_compare(cmd->name, "export") == 0)
		exec_export(shell, cmd);
	else if (str_compare(cmd->name, "pwd") == 0)
		exec_pwd(shell);
	else if (str_compare(cmd->name, "unset") == 0)
		exec_unset(shell, cmd);
}
