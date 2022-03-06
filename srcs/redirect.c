/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 21:00:04 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/06 15:42:47 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(t_cmd *cmd)
{
	int	fd;

	if (cmd->redirect_id == id_in_std)
		fd = open(cmd->redirect_path, O_RDONLY, S_IRWXU);
	if (cmd->redirect_id == id_in_file)
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
	return (0);
}

int	redirect_output(t_cmd *cmd)
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
	return (0);
}

void	handle_redirect(t_cmd *cmd)
{
	if (cmd->redirect_id == id_in_std || cmd->redirect_id == id_in_file)
		redirect_input(cmd);
	if (cmd->redirect_id == id_out_write || cmd->redirect_id == id_out_append)
		redirect_output(cmd);
}
