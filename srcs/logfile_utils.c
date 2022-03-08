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
 * @brief Retourne le temps sous forme d'un compteur
 * 
 * @return int 
 */
int	ft_gettime(void)
{
	static int	time;

	time++;
	return (time);
}

/**
 * @brief Ouvre un fichier log
 * 
 * @return int 
 */
int	log_open(void)
{
	mode_t		mode;
	static char	logfilename[200];
	char		*filename;

	if (*logfilename == '\0')
	{
		if (getcwd(logfilename, sizeof(logfilename)))
		{
			filename = str_joins(logfilename, LOGFILE, "/");
			ft_strlcpy(logfilename, filename, 200);
			free(filename);
		}
	}
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	return (open(logfilename, O_WRONLY | O_APPEND | O_CREAT, mode));
}
