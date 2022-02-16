/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libparser_tester.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:15:55 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/16 15:08:27 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libparser.h"
#include "libparser_tester.h"
#include <stdlib.h>
#include <stdio.h>

int	main(int __attribute__((unused)) argc, char __attribute__((unused)) **argv)
{
	//test_automaton();
	valid_automaton("blabla");
	valid_automaton("\"blabla\"");
	token_automaton_tester("read -p \"Entrez un numero : \"int1\n");
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

void	valid_automaton(char *str)
{
	t_automaton	*oto;
	int			ret;

	oto = automaton_factory("tests/automate.conf");
	ret = automaton_validator(oto, str);
	printf("value : {%s} return : %d\n", str, ret);
	automaton_dispose(oto);
}

void	test_automaton(void)
{
	t_automaton	*oto;
	int			i;
	int			j;

	oto = automaton_factory("tests/automate.conf");
	printf("size\n%d %d \n", oto->cols, oto->rows);
	printf("%d \n", oto->char_indexes['"']);
	i = -1;
	printf("transitions \n");
	while (++i < oto->rows)
	{
		j = 0;
		while (j < oto->cols)
		{
			printf("%d ", oto->transitions[j + (i * oto->cols)]);
			j++;
		}
		printf("\n");
	}
	i = -1;
	printf("accepting \n");
	while (++i < oto->rows)
		printf("%d ", oto->accepting[i]);
	automaton_dispose(oto);
}

void	token_print(t_token *token)
{
	while (token)
	{
		printf("token : [%-15s], start : [%2d], id : [%2d]\n", token->str, 
			token->col, token->id);
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

/**
 * @brief vérfication de la génération de jeton
 * 
 * @return int 
 */
int	token_automaton_tester(char *input)
{
	t_token		*token;
	t_automaton	*oto;

	oto = automaton_factory("tests/automate.conf");
	printf("\ninput : %s\n\n", input);
	token = automaton_token(oto, input);
	token_print(token);
	token_dispose(&token);
	printf("\n\n");
	return (1);
}
