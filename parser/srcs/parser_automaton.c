/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_automaton.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 10:55:31 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/12 17:52:29 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libparser.h"
#include "parser_automaton.h"
#include "libft.h"

int	allocate_automaton(t_automaton	*au)
{
	au->char_indexes = ft_calloc(sizeof(char), CHAR_INDEXES_LEN);
	au->transitions = malloc(sizeof(int) * au->rows * au->cols);
	au->accepting = malloc(sizeof(int) * au->rows);
	return (1);
}

t_automaton	*automaton_factory(char *filename)
{
	char		*line;
	int			fd;
	t_automaton	*oto;

	oto = ft_calloc(sizeof(t_automaton), 1);
	if (!oto)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd > -1)
	{
		auto_load_size(fd, oto);
		allocate_automaton(oto);
		read_ignore_comment(&line, fd);
		auto_load_indexes(line, oto);
		auto_load_transitions(fd, oto);
		read_ignore_comment(&line, fd);
		auto_load_accepting(line, oto);
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
