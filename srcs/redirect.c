/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 21:00:04 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/11 02:30:55 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirect_file(t_shell *shell, t_cmd *cmd)
{
	if (cmd->redirect_id == id_in_std || cmd->redirect_id == id_in_file)
		redirect_input_file(shell, cmd);
	if (cmd->redirect_id == id_out_write || cmd->redirect_id == id_out_append)
		redirect_output_file(cmd);
}

void	redirect_input_file(t_shell *shell, t_cmd *cmd)
{
	int	fd;

	(void)shell;
	fd = open(cmd->redirect_path, O_RDONLY, S_IRWXU);
	if (fd == -1)
	{
		perror("Error: open() failed");
		exit(1);
	}
	else if (fd > 0)
	{
		dup2(fd, 0);
		close(fd);
	}
}

void	redirect_output_file(t_cmd *cmd)
{
	int	fd;

	if (cmd->redirect_id == id_out_write)
		fd = open(cmd->redirect_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (cmd->redirect_id == id_out_append)
		fd = open(cmd->redirect_path, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	if (fd == -1)
	{
		perror("Error: open() failed");
		exit(1);
	}
	else if (fd > 0)
	{
		dup2(fd, 1);
		close(fd);
	}
}

void	redirect_input(t_shell *shell, t_cmd *cmd, int num)
{
	if (num > 0)
	{
		if (cmd->redirect_id == id_in_std || cmd->redirect_id == id_in_file)
			redirect_input_file(shell, cmd);
		else
			dup2(shell->pipes[num - 1][0], 0);
	}
	else if (num == 0)
		redirect_input_file(shell, cmd);
}

void	redirect_output(t_shell *shell, t_cmd *cmd, int num)
{
	if (num < shell->num_cmds - 1)
	{
		if (cmd->redirect_id == id_out_write
			|| cmd->redirect_id == id_out_append)
			redirect_output_file(cmd);
		else
			dup2(shell->pipes[num][1], 1);
	}
	else if (num == shell->num_cmds - 1)
		redirect_output_file(cmd);
}
