/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 21:00:04 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/11 02:30:26 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(t_shell *shell, t_cmd *cmd, int num)
{
	int		fd;
	char	*line;
	char	*delimit;
	char	*tmp_file;

	tmp_file = here_doc_tmpfile(shell, num);
	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (fd > -1)
	{
		write(fd, "", 0);
		line = here_doc_readline();
		delimit = cmd->redirect_path;
		while (!(ft_strncmp(delimit, line, ft_strlen(delimit)) == 0
				&& (ft_strlen(delimit) + 1) == ft_strlen(line)))
		{
			write(fd, line, ft_strlen(line));
			free(line);
			line = here_doc_readline();
		}
		free(line);
	}
	close(fd);
	free(cmd->redirect_path);
	cmd->redirect_path = tmp_file;
	return (fd);
}

/**
 * @brief lit la ligne sur l'entrée standard
 * 
 * @param fd 
 * @return char* 
 */
char	*here_doc_readline(void)
{
	ft_printf("> ");
	return (get_nextline(0));
}

/**
 * @brief retourne le nom d'un fichier temporaire
 * 
 * @param shell 
 * @return char* 
 */
char	*here_doc_tmpfile(t_shell *shell, int num)
{
	char	*tmp_id;
	char	*tmp_file;

	tmp_id = ft_itoa(num);
	if (!tmp_id)
		return (0);
	tmp_file = str_joins(shell->workink_dir, tmp_id, "/.tmp/.heredoc");
	free(tmp_id);
	if (!tmp_file)
		return (0);
	return (tmp_file);
}
