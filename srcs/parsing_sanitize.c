/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sanitize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 08:51:29 by dthalman          #+#    #+#             */
/*   Updated: 2022/03/09 19:32:24 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Supprime les guillements d'un element de la liste
 *
 * @param t
 */
static void	sanitize_quotes_word_token(t_shell *shell, t_token *token)
{
	int	i;
	int	len;
	int	decal;
	char *tmp;

	i = 0;
	decal = 0;
	len = ft_strlen(token->str);
	while (i < len - decal)
	{
		//if (token->str[i + decal] == '\'' || token->str[i + decal] == '"')
		//	decal++;
		if (token->id == id_single_quotes && token->str[i] == '\'')
		{
			decal++;
		}
		if (token->id != id_single_quotes && token->str[i] == '"')
		{
			decal++;
		}
		token->str[i] = token->str[i + decal];
		i++;
	}
	printf("%c\n", token->str[i-1]);
	token->str[i] = 0;
	if (token->id != id_single_quotes)
	{
		tmp = evaluate_str_env(shell, token->str, 0);
		free(token->str);
		token->str = tmp;
	}
	printf("id: %d str: |%s| decal: %d\n", token->id, token->str, decal);
	// while (++i < len - decal)
	// {
	// 	if (token->str[i + decal] == '\'' || token->str[i + decal] == '"')
	// 		decal++;
	// 	token->str[i] = token->str[i + decal];
	// }
}

/**
 * @brief supprime les guillements de toute la liste
 *
 * @param token
 */
void	sanitize_quotes_token(t_shell *shell, t_token *tokens)
{
	t_token	*token;

	token = tokens;
	while (token)
	{
		if (token->id == id_dbl_quotes || token->id == id_single_quotes
			|| token->id == id_word)
			sanitize_quotes_word_token(shell, token);
		token = token->next;
	}
}
