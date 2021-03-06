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
 * @brief Crée un nouveau jeton à partir des informations
 * de position de la chaine initiale à parser
 * 
 * @param ppos 
 * @return t_token* 
 */
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
 * @brief Compte le nombre de jeton rpésent dans une liste
 * de jeeton
 * 
 * @param token 
 * @return int 
 */
int	count_token(t_token *from, t_token *to)
{
	int	count;

	count = 0;
	while (from)
	{
		count++;
		if (to && from == to)
			break ;
		from = from->next;
	}
	return (count);
}

/**
 * @brief Ajoute un jeton dans la structure des jeton.
 * 
 * @param token liste de jeton
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

/**
 * @brief Libère la mémoire alloué pour les jetons
 * 
 * @param token 
 */
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
	*token = NULL;
}
