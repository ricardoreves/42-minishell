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
#include "libft.h"

void	read_ignore_comment(char **line, int fd)
{
	line = get_nextline(fd);
	while (*line && (*line)[0] == '#') // ignore comment #
	{
		free(*line);
		*line = get_nextline(fd);
	}
}

t_automaton	*automaton_factory(char *filename)
{
	char		*line;
	char		*str;
	int			fd;
	t_automaton *oto;

	oto = calloc(sizeof(t_automaton), 1);
	fd = open(filename, O_RDONLY);
	if (fd > -1)
	{
		read_ignore_comment(&line, fd);
		printf("%s", line);
		str = line;
		oto->cols = ft_atoi(str);
		while (*str && is_space(*str))
			str++;
		while (*str && is_digit(*str))
			str++;
		oto->rows = ft_atoi(str);
		free(line);
		oto->char_indexes = malloc(sizeof(char) * 256);
		oto->transitions = malloc(sizeof(int) * oto->rows * oto->cols);
		oto->accepting = malloc(sizeof(int) * oto->cols);
		read_ignore_comment(&line, fd);
	}
	close(fd);
	return (oto);
}

void	automaton_dispose(t_automaton *au)
{
	free(au->char_indexes);
	free(au->transitions);
	free(au->accepting);
	free(au);
}