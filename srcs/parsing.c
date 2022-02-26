/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 08:51:29 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/25 14:59:31 by dthalman         ###   ########.fr       */
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
char	**token_to_string(t_token *token)
{
	char		**args;
	int			i;
	int			strlen;

	args = malloc(sizeof(char **) * (count_token(token) + 1));
	i = 0;
	while (token)
	{
		strlen = ft_strlen(token->str);
		args[i] = malloc(sizeof(char *) * (strlen + 1));
		if (args[i])
			ft_strlcpy(args[i], token->str, strlen + 1);
		token = token->next;
		i++;
	}
	args[i] = 0;
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

	oto = automaton_factory(cfg);
	automaton_token(&token, oto, shell->cmdline);
	sanatize_quotes_token(token);
	exec_ident_token(token, shell);
	if (token)
		args = token_to_string(token);
	else
		args = NULL;
	token_dispose(&token);
	automaton_dispose(oto);
	return (args);
}

t_parse_tree	*parse_tree(char __attribute__((unused)) **str)
{
	t_parse_tree	*tree;

	tree = malloc(sizeof(t_parse_tree *));
	return (tree);
}