/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 08:51:29 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/04 17:18:57 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libparser.h"
#include "libft.h"
#include "parser_automaton.h"
#include <stdlib.h>

/**
 * @brief déplace le curseur de position de la chaine tant qu'il
 * s'agit 
 * 
 * @param s 
 * @param pos 
 */
void	move_space_forward(char const *s, int *pos)
{
	while (s[*pos] && is_space(s[*pos]))
		(*pos)++;
}

t_token	*new_token(t_parse_pos *ppos)
{
	t_token	*t;

	t = malloc(sizeof(t_token));
	if (t)
	{
		t->next = 0;
		t->col = ppos->col;
		t->id = ppos->id;
		t->row = ppos->row;
		t->str = malloc(ppos->len + 1);
		if (!t->str)
		{
			free(t);
			t = 0;
		}
	}
	return (t);
}

/**
 * @brief Ajoute un jeton dans la structure des jeton.
 * 
 * @param token liste de jeton
 * @param start position de départ de la chaine
 * @param len longueur de la chaine
 * @param pos position dans la chaine de départ
 */
void	add_token(t_token **token, t_parse_pos *ppos)
{
	t_token	*t;
	t_token	*t2;
	int		i;
	char	*start;

	start = ppos->str + ppos->start_pos;
	t = new_token(ppos);
	if (!t)
		return ;
	i = -1;
	while (++i < ppos->len)
		t->str[i] = start[i];
	t->str[i] = 0;
	if (!(*token))
		*token = t;
	else
	{
		t2 = (*token);
		while (t2->next)
			t2 = t2->next;
		t2->next = t;
	}
}

void	token_dispose(t_token **token)
{
	t_token	*t;
	t_token	*p;

	t = *token;
	while (t)
	{
		p = t;
		t = t->next;
		free(p->str);
		free(p);
	}
	*token = 0;
}

/*
t_token	*parse_token(char *str)
{
	t_token		*token;
	t_parse_pos	ppos;
	int			final;

	init_parse_pos(&ppos, str);
	token = 0;
	if (!str || !*str)
		return (0);
	ppos.str = str;
	ppos.id = 0;
	while (ppos.str[ppos.end_pos])
	{
		move_space_forward(ppos.str, &ppos.end_pos);
		ppos.start_pos = ppos.end_pos;
		if (ppos.str[ppos.end_pos] && ppos.str[ppos.end_pos] == '"')
		{
			ppos.end_pos++;
			final = 0;
			while (ppos.str[ppos.end_pos] && !final)
			{
				ppos.end_pos++;
				if (ppos.str[ppos.end_pos] == '\\')
				{
					ppos.end_pos++;
					if (ppos.str[ppos.end_pos] == '"')
					{
						ppos.end_pos++;
					}
				} 
				else if (ppos.str[ppos.end_pos] == '"')
					final = 1;
			}
			if (final)
			{
				ppos.len = ppos.end_pos - ppos.start_pos + 1;
				add_token(&token, &ppos);
				ppos.end_pos++;
			}
		}
		else if (ppos.str[ppos.end_pos] && ppos.str[ppos.end_pos] == '\'')
		{
			final = 0;
			while (ppos.str[ppos.end_pos] && !final)
			{
				ppos.end_pos++;
				if (ppos.str[ppos.end_pos] == '\\')
				{
					ppos.end_pos++;
					if (ppos.str[ppos.end_pos] == '\'')
					{
						ppos.end_pos++;
					}
				} 
				else if (ppos.str[ppos.end_pos] == '\'')
					final = 1;
			}
			if (final)
			{
				ppos.len = ppos.end_pos - ppos.start_pos + 1;
				add_token(&token, &ppos);
				ppos.end_pos++;
			}
		}
		else if (ppos.str[ppos.end_pos] && ppos.str[ppos.end_pos] == '<')
		{
			if (ppos.str[ppos.end_pos + 1] == '<')
			{
				ppos.end_pos++;
			}
			ppos.len = ppos.end_pos - ppos.start_pos + 1;
			add_token(&token, &ppos);
			ppos.end_pos++;
		}
		else if (ppos.str[ppos.end_pos] && ppos.str[ppos.end_pos] == '>')
		{
			if (ppos.str[ppos.end_pos + 1] == '>')
				ppos.end_pos++;
			ppos.len = ppos.end_pos - ppos.start_pos + 1;
			add_token(&token, &ppos);
			ppos.end_pos++;
		}
		else if (ppos.str[ppos.end_pos] && ppos.str[ppos.end_pos] == '|')
		{
			ppos.len = 1;
			add_token(&token, &ppos);
			ppos.end_pos++;
		}
		else if (ppos.str[ppos.end_pos] && ppos.str[ppos.end_pos] == ';')
		{
			ppos.len = 1;
			add_token(&token, &ppos);
			ppos.end_pos++;
		}
		else if (ppos.str[ppos.end_pos] && ppos.str[ppos.end_pos] == '&')
		{
			if (ppos.str[ppos.end_pos + 1] == '&')
			{
				ppos.end_pos++;
			}
			ppos.len = ppos.end_pos - ppos.start_pos + 1;
			add_token(&token, &ppos);
			ppos.end_pos++;
		}
		else if(ppos.str[ppos.end_pos])
		{
			final = 0;
			while (ppos.str[ppos.end_pos] && !final)
			{
				if (!strchr(NON_CHAR_IDENTIFIER, ppos.str[ppos.end_pos]))
				{
					ppos.end_pos++;	
				}
				else
					final = 1;
			}
			ppos.len = ppos.end_pos - ppos.start_pos + 1;
			add_token(&token, &ppos);
		}
	}
	return (token);
}
*/