/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libparser_tester.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:15:55 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/26 14:53:41 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libparser.h"
#include "libparser_tester.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Affiche dans la console le tableau de transition
 * 
 * @param oto 
 */
void	test_print_transition(t_automaton *oto)
{
	int	i;
	int	j;

	i = -1;
	printf("\ntransitions \n");
	while (++i < oto->rows)
	{
		j = 0;
		while (j < oto->cols)
		{
			printf("%2d ", oto->transitions[j + (i * oto->cols)]);
			j++;
		}
		printf("\n");
	}
}

/**
 * @brief imprime à l'écran l'état du contenu des jetons
 * 
 * @param token 
 */
void	token_print(t_token *token)
{
	if (!token)
	{
		perror("input command line");
	}
	while (token)
	{
		printf("token : [%-15s], start : [%2d], id : [%2d]\n", token->str,
			token->col, token->id);
		token = token->next;
	}
}
