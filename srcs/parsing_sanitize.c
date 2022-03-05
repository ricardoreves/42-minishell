/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sanitize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 08:51:29 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/28 17:59:24 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Supprime les guillements d'un element de la liste
 *
 * @param t
 */
void sanitize_quotes_word_token(t_token *t)
{
	int	len;
	int	i;
	int	decal;

	len = ft_strlen(t->str);
	i = -1;
	decal = 0;
	while (++i < len - decal)
	{
		if (t->str[i + decal] == '\'' || t->str[i + decal] == '"')
			decal++;
		t->str[i] = t->str[i + decal];
	}
	t->str[i] = 0;
}

/**
 * @brief supprime les guillements de toute la liste
 *
 * @param token
 */
void sanitize_quotes_token(t_token *token)
{
	t_token	*t;

	t = token;
	while (t)
	{
		if (t->id == id_dbl_quotes || t->id == id_single_quotes
			|| t->id == id_word)
			sanitize_quotes_word_token(t);
		t = t->next;
	}
}
