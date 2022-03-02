/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:30:18 by dthalman          #+#    #+#             */
/*   Updated: 2022/03/02 13:30:18 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include "minishell.h"

/**
 * @brief Retourne le temps en microseconde 
 * 
 * ATTENTION DE SUPPRIMER CETTE PARTIE
 * CE N'EST PAS SUPPORTER PAR LE SUJET
 * 
 * @return int 
 */
int	ft_gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((int)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

int	log_open(void)
{
	mode_t	mode;
	
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	return (open("minishell.log", O_WRONLY | O_APPEND | O_CREAT, 0644));
}

void	log_message(char *msg)
{
	int		fd;
	
	fd = log_open();
	if (fd > -1)
	{
		ft_fprintf(fd, "%d\t%s\n", ft_gettime(), msg);
		close(fd);
	}
	else
		perror("minishell");
}

void	log_token(t_token *token)
{
	int		fd;

	fd = log_open();
	if (fd > -1)
	{
		if (!token)
		{
			perror("input command line");
		}
		while (token)
		{
			ft_fprintf(fd, "%d\ttoken : [%-15s], start : [%2d], id : [%2d]\n",
				ft_gettime(), token->str, token->col, token->id);
			token = token->next;
		}
		close(fd);
	}
	else 
		perror("minishell");
}
