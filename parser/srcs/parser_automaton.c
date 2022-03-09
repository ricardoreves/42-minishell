/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_automaton.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 10:55:31 by dthalman          #+#    #+#             */
/*   Updated: 2022/03/09 09:58:54 by dthalman         ###   ########.fr       */
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
		auto_load_indexes(fd, oto);
		auto_load_transitions(fd, oto);
		auto_load_accepting(fd, oto);
		dispose_list_line();
		close(fd);
	}
	else
		perror("automaton");
	return (oto);
}

t_automaton	*automaton_wildcard_factory(char *str)
{
	t_automaton	*oto;

	oto = ft_calloc(sizeof(t_automaton), 1);
	if (!oto)
		return (NULL);
	auto_load_str_size(str, oto);
	allocate_automaton(oto);
	auto_load_str_indexes(str, oto);
	auto_load_str_transitions(str, oto);
	auto_load_str_accepting(oto);
	return (oto);
}

void	automaton_dispose(t_automaton *au)
{
	free(au->char_indexes);
	free(au->transitions);
	free(au->accepting);
	free(au->indexes_of_char);
	free(au);
}

int	automaton_validator(t_automaton *au, char *str)
{
	int	step;
	int	last_accepted;
	int	col;

	step = 0;
	last_accepted = 0;
	while (step < au->rows && *str)
	{
		col = get_char_index((int)*str, au);
		step = au->transitions[col + (step * au->cols)];
		if (step < au->rows)
			last_accepted = au->accepting[step];
		str++;
	}
	col = get_char_index((int)*str, au);
	if (step < au->rows)
	{
		step = au->transitions[col + (step * au->cols)];
		if (step < au->rows)
			last_accepted = au->accepting[step];
	}
	return (last_accepted);
}
