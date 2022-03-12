/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 21:00:04 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/12 02:12:59 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(t_shell *shell, t_cmd *cmd, char *eof)
{
	char	*tmp_file;
	char	*line;
	int		fd;

	tmp_file = get_tempfilename(shell);
	fd = open(tmp_file, O_WRONLY | O_CREAT, 0664);
	if (fd > -1)
	{
		line = here_doc_readline();
		while (!(ft_strncmp(eof, line, ft_strlen(eof)) == 0
				&& (ft_strlen(eof) + 1) == ft_strlen(line)))
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
	cmd->redirect_id = id_in_file;
}

/**
 * @brief retourne le nom d'un fichier temporaire
 * 
 * @param shell 
 * @return char* 
 */
char	*get_tempfilename(t_shell *shell)
{
	int		i;
	char	*base;
	char	*number;
	char	*filename;

	i = 1;
	base = ft_strjoin(shell->working_dir, "/.tmp/.minishell");
	number = ft_itoa(i);
	filename = str_joins(base, ".tmp", number);
	while (access(filename, F_OK) == 0)
	{	
		free(number);
		free(filename);
		number = ft_itoa(++i);
		filename = str_joins(base, ".tmp", number);
	}
	free(base);
	free(number);
	return (filename);
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
 * @brief crée un fichier temporaire par commande pour tous les here doc
 * 
 * @param shell 
 */
void	prepare_here_doc_cmd(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmds;
	while (cmd)
	{
		if (cmd->redirect_id == id_in_std)
			here_doc(shell, cmd, cmd->redirect_path);
		cmd = cmd->next;
	}
}
