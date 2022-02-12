/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libparser_tester.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:15:55 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/12 10:25:48 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libparser.h"
#include "libparser_tester.h"
#include <stdlib.h>
#include <stdio.h>

int	main(int __attribute__((unused)) argc, char __attribute__((unused)) **argv)
{
	t_automaton *oto;

	oto = automaton_factory("tests/automate.conf");
	printf("%d %d \n", oto->cols, oto->rows);
	printf("%d \n", oto->char_indexes['"']);
	automaton_dispose(oto);
return (0);
	token_tester("read -p \"Entrez un numéro : \" int1\n");
	token_tester("echo \"out\">>fichier");
	token_tester("commande>fichier");
	token_tester("commande<fichier");
	token_tester("commande|fichier");
	token_tester("commande |fichier");
	token_tester("commande | \"fichier\"");
	token_tester("commande |fichier << test >autre; ls /test/truc && autre");
	token_tester("commande <<sep");
	token_tester("'commande' fichier");
	token_tester("echo te'st'");
	token_tester("echo te\"st\";echo merci");
	token_tester("ls *.c");
	return (0);
}

void	token_print(t_token *token)
{
	while (token)
	{
		printf("token : [%-15s], start : [%2d]\n", token->str, token->position);
		token = token->next;
	}
}

/**
 * @brief vérfication de la génération de jeton
 * 
 * @return int 
 */
int	token_tester(char *input)
{
	t_token	*token;

	printf("\ninput : %s\n\n", input);
	token = parse_token(input);
	token_print(token);
	token_dispose(&token);
	printf("\n\n");
	return (1);
}
