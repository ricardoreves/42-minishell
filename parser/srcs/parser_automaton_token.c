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

void	automaton_token_analys(t_parse_pos *ppos, t_token **token,
	t_automaton *au, char *str)
{
	int			col;

	ppos->start_pos = ppos->end_pos;
	ppos->col += ppos->len;
	ppos->step = 0;
	ppos->last_step = 0;
	while (ppos->step < au->rows && str[ppos->end_pos])
	{
		ppos->last_step = ppos->step;
		col = get_char_index((int)str[ppos->end_pos], au);
		ppos->step = au->transitions[col + (ppos->step * au->cols)];
		ppos->end_pos++;
	}
	if (ppos->last_step < au->rows)
	{
		ppos->id = au->accepting[ppos->last_step];
		if (ppos->id)
		{
			ppos->len = ppos->end_pos - ppos->start_pos - 1;
			add_token(token, ppos);
		}
	}
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

	token = 0;
	init_parse_pos(&ppos, str);
	while (str[ppos.end_pos])
		automaton_token_analys(&ppos, &token, au, str);
	return (token);
}
