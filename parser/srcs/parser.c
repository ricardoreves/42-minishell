/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 08:51:29 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/18 14:59:39 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libparser.h"
#include "libft.h"
#include <stdlib.h>

char	**parse(char *str, char *cfg)
{
	char		**args;
	t_token		*token;
	t_automaton	*oto;
	int			i;
	int			strlen;

	oto = automaton_factory(cfg);
	automaton_token(&token, oto, str);
	if (!token)
		return (NULL);
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
