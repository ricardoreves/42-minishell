/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 08:51:29 by dthalman          #+#    #+#             */
/*   Updated: 2022/03/10 01:19:00 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief parse une chaine de caractère et retourne
 * une liste de chaine de caractère en fonction du
 * parsing
 *
 * @param shell
 * @return int
 */
int	parse_command_line(t_shell *shell)
{
	t_token		*token;
	t_automaton	*oto;

	oto = automaton_factory(shell->config);
	automaton_token(&token, oto, shell->cmdline);
	sanitize_quotes_token(shell, token);
	shell->cmds = 0;
	shell->num_cmds = 0;
	if (token)
	{
		prepare_cmds(token, shell);
		wildcard_cmds(shell);
	}
	log_token(token);
	token_dispose(&token);
	automaton_dispose(oto);
	return (shell->num_cmds);
}

/**
 * @brief 
 * 
 * @param shell 
 * @param token 
 */
void	evaluate_quotes_token(t_shell *shell, t_token *token)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_calloc(sizeof(char), ft_strlen(token->str) + 1);
	while (token->str[i])
	{
		if ((token->id == id_single_quotes && token->str[i] == '\'')
			|| (token->id != id_single_quotes && token->str[i] == '"'))
			i++;
		else
			tmp[j++] = token->str[i++];
	}
	free(token->str);
	token->str = tmp;
	if (token->id != id_single_quotes)
	{
		tmp = evaluate_str_env(shell, token->str, 0);
		free(token->str);
		token->str = tmp;
	}
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
			evaluate_quotes_token(shell, token);
		token = token->next;
	}
}
