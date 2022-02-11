/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_automaton.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 10:55:31 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/11 10:55:31 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libparser.h"

t_automaton	*automaton_factory(char *filename)
{
	char		*line;
	int			fd;
	t_automaton *oto;

	oto = calloc(sizeof(t_automaton), 1);
	fd = open(filename, O_RDONLY);
	if (fd > -1)
	{
		line = get_nextline(fd);
		while (line)
		{
			if (line[0] != '#')
				printf("%s", line);
			free(line);
			line = get_nextline(fd);
		}
		free(line);
	}
	close(fd);
	return (oto);
}