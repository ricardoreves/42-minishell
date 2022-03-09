/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 21:00:04 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/09 16:57:25 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirect_file(t_shell *shell, t_cmd *cmd)
{
	if (cmd->redirect_id == id_in_std || cmd->redirect_id == id_in_file)
		redirect_input_file(cmd);
	if (cmd->redirect_id == id_out_write || cmd->redirect_id == id_out_append)
		redirect_output_file(shell, cmd);
}

void	redirect_input_file(t_cmd *cmd)
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
}

void	redirect_output_file(t_shell *shell, t_cmd *cmd)
{
	int	fd;

	if (cmd->redirect_id == id_out_write)
		fd = here_doc(shell, cmd->redirect_path);
		//fd = open(cmd->redirect_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
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
		// printf("input -> %s pipe: [%d][0] std: 0\n", cmd->name, num - 1);
		if (cmd->redirect_id == id_in_std || cmd->redirect_id == id_in_file)
			redirect_input_file(cmd);
		else
			dup2(shell->pipes[num - 1][0], 0);
	}
	else if (num == 0)
		redirect_input_file(cmd);
}

void	redirect_output(t_shell *shell, t_cmd *cmd, int num)
{
	if (num < shell->num_cmds - 1)
	{
		// printf("output -> %s pipe: [%d][1] std: 1\n", cmd->name, num);
		if (cmd->redirect_id == id_out_write
			|| cmd->redirect_id == id_out_append)
			redirect_output_file(shell, cmd);
		else
			dup2(shell->pipes[num][1], 1);
	}
	else if (num == shell->num_cmds - 1)
		redirect_output_file(shell, cmd);
}

int	here_doc(t_shell *shell, char *eof)
{
	char	*tmp_file;
	char	*line;
	int		fd;
	int		mode;

	tmp_file = str_joins(shell->workink_dir, ".minishell.tmp", "/");
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	fd = open(tmp_file, O_WRONLY | O_APPEND | O_CREAT, mode);
	if (fd > -1)
	{
		line = get_nextline(0);
		while (!ft_strncmp(eof, line, ft_strlen(eof)) &&
			(ft_strlen(eof) + 1) == ft_strlen(line))
		{
			write(fd, line, ft_strlen(line));
			free(line);
			line = get_nextline(0);
		}
		free(line);
	}
	close(fd);
	fd = open(tmp_file, O_RDONLY, mode);
	free(tmp_file);
	return (fd);
}