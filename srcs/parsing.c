/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 08:51:29 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/26 10:28:39 by dthalman         ###   ########.fr       */
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
char	**token_to_string(t_token *token_from, t_token *token_to)
{
	char		**args;
	int			i;

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
char	**parse(t_shell *shell, char *cfg)
{
	char		**args;
	t_token		*token;
	t_automaton	*oto;
	t_cmd		*cmds;

	oto = automaton_factory(cfg);
	automaton_token(&token, oto, shell->cmdline);
	sanatize_quotes_token(token);
	exec_ident_token(token, shell);
	cmds = NULL;
	prepare_cmd(token, &cmds);
	print_cmd(cmds);
	free_cmd(&cmds);
	if (token)
		args = token_to_string(token, NULL);
	else
		args = NULL;
	token_dispose(&token);
	automaton_dispose(oto);
	return (args);
}
