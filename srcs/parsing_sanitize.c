/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sanitize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 08:51:29 by dthalman          #+#    #+#             */
/*   Updated: 2022/03/06 15:37:48 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Supprime les guillements d'un element de la liste
 *
 * @param t
 */
static void sanitize_quotes_word_token(t_token *token)
{
	int len;
	int i;
	int decal;

	i = -1;
	decal = 0;
	len = ft_strlen(token->str);
	while (++i < len - decal)
	{
		if (token->str[i + decal] == '\'' || token->str[i + decal] == '"')
			decal++;
		token->str[i] = token->str[i + decal];
	}
	token->str[i] = 0;
}

/**
 * @brief supprime les guillements de toute la liste
 *
 * @param token
 */
void sanitize_quotes_token(t_token *tokens)
{
	t_token *token;

	token = tokens;
	while (token)
	{
		if (token->id == id_dbl_quotes || token->id == id_single_quotes
			|| token->id == id_word)
			sanitize_quotes_word_token(token);
		token = token->next;
	}
}
