/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 21:00:04 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/09 22:38:32 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(t_shell *shell, char *eof)
{
	char	*tmp_file;
	char	*line;
	int		fd;
	int		mode;

	tmp_file = get_tempfilename(shell);
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	fd = open(tmp_file, O_WRONLY | O_CREAT, mode);
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
	fd = open(tmp_file, O_RDONLY, mode);
	free(tmp_file);
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
char	*get_tempfilename(t_shell *shell)
{
	int 	i;
	char	*base;
	char	*number;
	char	*filename;

	i = 1;
	base = ft_strjoin(shell->workink_dir, "/.tmp/.minishell");
	number = get_strnbr(i);
	filename = str_joins(base, ".tmp", number);
	while (access(filename, F_OK) == 0)
	{	
		free(number);
		free(filename);
		number = get_strnbr(++i);
		filename = str_joins(base, ".tmp", number);
	}
	free(base);
	free(number);
	return (filename);
}

/**
 * @brief retourne une chaine de caractère représentant un entier uniquement
 * positif
 * 
 * @param n 
 * @return char* 
 */
char	*get_strnbr(int n)
{
	int		len;
	int		i;
	char	*str;

	len = 0;
	i = n;
	while (i != 0)
	{
		i = i / 10;
		len++;
	}
	str = malloc(len + 1);
	str[len] = 0;
	while (len--)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

/**
 * @brief crée un fichier temporaire par commande pour tous les here doc
 * 
 * @param shell 
 */
void	prepare_here_doc_cmd(t_shell *shell)
{
	t_cmd *cmd;

	cmd = shell->cmds;
	while (cmd)
	{
		if (cmd->redirect_id == id_in_std)
			here_doc(shell, cmd, cmd->redirect_path);
		cmd = cmd->next;
	}
}
