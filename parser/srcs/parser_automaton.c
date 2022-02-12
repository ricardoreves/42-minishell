/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_automaton.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 10:55:31 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/12 10:24:07 by dthalman         ###   ########.fr       */
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
	*line = get_nextline(fd);
	while (*line && (*line)[0] == '#') // ignore comment #
	{
		free(*line);
		*line = get_nextline(fd);
	}
}

void	auto_load_size(int fd, t_automaton *au)
{
	char	*str;
	char	*line;

	read_ignore_comment(&line, fd);
	str = line;
	au->cols = ft_atoi(str);
	while (*str && is_space(*str))
		str++;
	while (*str && is_digit(*str))
		str++;
	au->rows = ft_atoi(str);
	free(line);
}

void	auto_load_indexes(char *str, t_automaton *au)
{
	int	c;
	int idx;

	while (str && *str)
	{
		while (*str && is_digit(*str))
			str++;
		c = ft_atoi(str);
		while (*str && is_digit(*str))
			str++;
		idx = ft_atoi(str);
		if (c < CHAR_INDEXES_LEN && idx < au->cols)
			au->char_indexes[c] = idx;
		if (!is_digit(*str) && !is_digit(*str))
			break ;
	}
}

t_automaton	*automaton_factory(char *filename)
{
	char		*line;
	int			fd;
	t_automaton *oto;

	oto = ft_calloc(sizeof(t_automaton), 1);
	if (!oto)
		return NULL;
	fd = open(filename, O_RDONLY);
	if (fd > -1)
	{
		auto_load_size(fd, oto);
		oto->char_indexes = ft_calloc(sizeof(char), CHAR_INDEXES_LEN);
		oto->transitions = malloc(sizeof(int) * oto->rows * oto->cols);
		oto->accepting = malloc(sizeof(int) * oto->cols);
		read_ignore_comment(&line, fd);
		auto_load_indexes(line, oto);
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