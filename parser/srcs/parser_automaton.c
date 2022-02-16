/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_automaton.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 10:55:31 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/16 20:29:52 by dthalman         ###   ########.fr       */
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

int	automaton_validator(t_automaton *au, char *str)
{
	int	step;
	int	last_step;
	int col;

	step = 0;
	last_step = 0;
	while (step != au->rows && str)
	{
		last_step = step;
		col = get_char_index((int)*str, au);
		step = au->transitions[col + (step * au->cols)];
		str++;
	}
	if (last_step == au->rows)
		return (0);
	return au->accepting[last_step];
}

void	init_parse_pos(t_parse_pos *ppos, char *str)
{
	ppos->col = 0;
	ppos->start_pos = 0;
	ppos->end_pos = 0;
	ppos->last_step = 0;
	ppos->row = 0;
	ppos->step = 0;
	ppos->len = 0;
	ppos->str = str;
}

t_token	*automaton_token(t_automaton *au, char *str)
{
	t_parse_pos	ppos;
	t_token		*token;
	int			col;

	token = 0;
	init_parse_pos(&ppos, str);
	while (str[ppos.end_pos])
	{
		ppos.start_pos = ppos.end_pos;
		ppos.col += ppos.len;
		ppos.step = 0;
		ppos.last_step = 0;
		while (ppos.step != au->rows && str[ppos.end_pos])
		{
			ppos.last_step = ppos.step;
			col = get_char_index((int)str[ppos.end_pos], au);
			ppos.step = au->transitions[col + (ppos.step * au->cols)];
			ppos.end_pos++;
		}
		if (ppos.last_step != au->rows)
		{
			ppos.id = au->accepting[ppos.last_step];
			if (ppos.id)
			{
				ppos.len = ppos.end_pos - ppos.start_pos -1;
				add_token(&token, &ppos);				
			}
		}
	}
	return (token);
}
