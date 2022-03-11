/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:35:14 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/11 17:39:53 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief execute toutes les commandes se trouvant dans shell->cmds
 * 
 * @param shell 
 */
void	handle_commands(t_shell *shell)
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
			if (!cmd->name)
				scan_stdin(cmd);
			process_command(shell, cmd, ++i);
			cmd = cmd->next;
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

// int	is_unexpected_token_command(t_shell *shell)
// {
// 	int	ret;

// 	ret = 0;
// 	if (!shell->cmds->name || shell->cmds->name)
// 	{
// 		show_command_error(shell, NULL,
// 			"syntax error near unexpected token", 2);
// 		save_exit_status(shell);
// 		return (1);
// 	}
// 	return (0);
// }

int	is_unexpected_token_command(t_shell *shell)
{
	t_cmd	*cmd;
	int		ret;

	ret = 0;
	cmd = shell->cmds;
	while (cmd)
	{
		if (!cmd->name)
			ret = 1;
		if (array_length(cmd->args) == 1 && ft_strncmp(cmd->name, "<", 1) == 0)
			ret = 1;
		if (array_length(cmd->args) == 1 && ft_strncmp(cmd->name, ">", 1) == 0)
			ret = 1;
		if (array_length(cmd->args) == 1 && ft_strncmp(cmd->name, "|", 1) == 0)
			ret = 1;
		cmd = cmd->next;
	}
	if (ret)
	{
		show_command_error(shell, "", MSG_SYNTAX_ERROR, 2);
		save_exit_status(shell);
		return (1);
	}
	return (0);
}