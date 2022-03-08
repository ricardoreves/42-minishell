/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:30:18 by dthalman          #+#    #+#             */
/*   Updated: 2022/03/06 17:45:42 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "minishell.h"

/**
 * @brief enregistre un message dans le fichier log
 * 
 * @param msg 
 */
void	log_message(char *msg)
{
	int		fd;

	fd = log_open();
	if (fd > -1)
	{
		ft_fprintf(fd, "%05d\t%s\n", ft_gettime(), msg);
		close(fd);
	}
	else
		perror("minishell");
}

/**
 * @brief Enregistre les enregistrements des jetons dans le fichier log
 * 
 * @param token 
 */
void	log_token(t_token *token)
{
	int		fd;

	fd = log_open();
	if (fd > -1)
	{
		while (token)
		{
			ft_fprintf(fd, "%05d\ttoken : [%-15s], start : [%2d], id : [%2d]\n",
				ft_gettime(), token->str, token->col, token->id);
			token = token->next;
		}
		close(fd);
	}
	else
		perror("minishell");
}

/**
 * @brief Enregistre le contenu de l'automate du parser dans le fichier log
 * 
 * @param au 
 */
void	log_automaton(t_automaton *au)
{
	int	fd;
	int	i;
	int	j;

	fd = log_open();
	ft_fprintf(fd, "automaton size\n%d %d \n", au->cols, au->rows);
	i = -1;
	ft_fprintf(fd, "transitions \n");
	while (++i < au->rows)
	{
		j = 0;
		while (j < au->cols)
		{
			ft_fprintf(fd, "%d ", au->transitions[j + (i * au->cols)]);
			j++;
		}
		ft_fprintf(fd, "\n");
	}
	i = -1;
	ft_fprintf(fd, "accepting \n");
	while (++i < au->rows)
		ft_fprintf(fd, "%d ", au->accepting[i]);
	close(fd);
}

/**
 * @brief Enregistre dans le fichier log les commandes
 * 
 * @param cmds 
 */
void	log_cmds(t_cmd *cmds)
{
	int		fd;
	char	**args;

	fd = log_open();
	if (fd > -1)
	{
		while (cmds)
		{
			ft_fprintf(fd, "%05d\tcmd name : [%s], redirect_id : [%d], args : ",
				ft_gettime(), cmds->name, cmds->redirect_id);
			args = cmds->args;
			while (args && *args)
			{
				ft_fprintf(fd, "[%s] ", *args);
				args++;
			}
			ft_fprintf(fd, "\n");
			cmds = cmds->next;
		}
		close(fd);
	}
	else
		perror("minishell");
}
