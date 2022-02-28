/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 08:51:29 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/28 03:10:28 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Convertie une liste de jeton en liste de chaine de
 * caractère
 *
 * @param token
 * @return char**
 */
char **token_to_string(t_token *token_from, t_token *token_to)
{
	char **args;
	int i;

	args = malloc(sizeof(char **) * (count_token(token_from, token_to) + 1));
	i = 0;
	while (token_from)
	{
		args[i] = ft_strdup(token_from->str);
		i++;
		if (token_from == token_to)
			break;
		token_from = token_from->next;
	}
	args[i] = NULL;
	return (args);
}

/**
 * @brief parse une chaine de caractère et retourne
 * une liste de chaine de caractère en fonction du
 * parsing
 *
 * @param str
 * @param cfg
 * @return char**
 */
char **parse_command_line(t_shell *shell)
{
	char **args;
	t_token *token;
	t_automaton *oto;

	oto = automaton_factory(shell->config);
	automaton_token(&token, oto, shell->cmdline);
	sanatize_quotes_token(token);
	exec_ident_token(token, shell);
	shell->cmds = NULL;
	prepare_cmds(token, &shell->cmds);
	print_cmds(shell->cmds);
	// free_cmd(&shell->cmds);
	//if (token)
	//	args = token_to_string(token, NULL);
	//else
		args = NULL;
	token_dispose(&token);
	automaton_dispose(oto);
	return (args);
}
