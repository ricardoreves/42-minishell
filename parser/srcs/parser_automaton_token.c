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
#include <errno.h>

void	automaton_token_next_step(t_parse_pos *ppos, t_automaton *au)
{
	int			col;
	int			accepting;

	col = get_char_index((int)ppos->str[ppos->end_pos], au);
	ppos->step = au->transitions[col + (ppos->step * au->cols)];
	if (ppos->step < au->rows)
	{
		accepting = au->accepting[ppos->step];
		if (accepting)
			ppos->accepting = accepting;
		ppos->end_pos++;
	}
}

int	automaton_token_analys(t_parse_pos *ppos, t_token **token,
	t_automaton *au)
{
	ppos->start_pos = ppos->end_pos;
	ppos->col += ppos->len;
	ppos->step = 0;
	ppos->accepting = 0;
	ppos->id = 0;
	automaton_token_next_step(ppos, au);
	while (ppos->step < au->rows && ppos->str[ppos->end_pos])
		automaton_token_next_step(ppos, au);
	if (ppos->accepting)
	{
		ppos->id = ppos->accepting;
		if (ppos->accepting > 0)
		{
			ppos->len = ppos->end_pos - ppos->start_pos;
			add_token(token, ppos);
		}
	}
	else
		return (0);
	return (1);
}

void	init_parse_pos(t_parse_pos *ppos, char *str)
{
	ppos->col = 0;
	ppos->start_pos = 0;
	ppos->end_pos = 0;
	ppos->accepting = 0;
	ppos->row = 0;
	ppos->step = 0;
	ppos->len = 0;
	ppos->str = str;
}

void	automaton_token(t_token **token, t_automaton *au, char *str)
{
	t_parse_pos	ppos;
	
	int			ret;

	*token = 0;
	ret = 1;
	init_parse_pos(&ppos, str);
	while (str[ppos.end_pos] && ret)
		ret = automaton_token_analys(&ppos, token, au);
	if (!ret)
	{
		errno = EINVAL;
		token_dispose(token);
	}
}
