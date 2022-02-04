/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 08:51:29 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/04 10:26:23 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include <stdlib.h>

char **ft_parse_token(char __attribute__((unused)) *str)
{
	char	**ret;

	ret = malloc(sizeof(char *));
	return (ret);
}

t_parse_tree	*ft_parse_tree(char __attribute__((unused)) **str)
{
	t_parse_tree	*tree;

	tree = malloc(sizeof(t_parse_tree *));
	return (tree);
}
