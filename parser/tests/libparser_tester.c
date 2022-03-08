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
 * @brief effectue les différents tests de validité du parser
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int	main(int __attribute__((unused)) argc, char __attribute__((unused)) **argv)
{
	test_automaton();
	valid_automaton("blabla");
	valid_automaton("\"blabla");
	valid_automaton("\"blabla\" ");
	valid_automaton_str("*", "actuel");
	valid_automaton_str("actu*", "actuel");
	valid_automaton_str("actu*", "atuel");
	valid_automaton_str("in*able", "incroyables");
	valid_automaton_str("in*able", "incroyble");
	valid_automaton_str("in*a*e", "incroyable");
	token_automaton_tester("1234|1234");
	token_automaton_tester("read -p | 'com\\\'' \t \"Entre | num : x\"i|nt1\n");
	token_automaton_tester("read -p |  \t \"Entrez");
	token_automaton_tester("commande>fichier");
	return (0);
}

/**
 * @brief Vérifie le fonctionnement de la validité d'une chaine dans l'automate
 * 
 * @param str 
 */
void	valid_automaton(char *str)
{
	t_automaton	*oto;
	int			ret;

	oto = automaton_factory("tests/automate.conf");
	ret = automaton_validator(oto, str);
	printf("value : {%s} return : %d\n", str, ret);
	automaton_dispose(oto);
}

/**
 * @brief Vérifie le fonctionnement de la validité d'une chaine dans l'automate
 * avec une base wildcard
 * 
 * @param str 
 */
void	valid_automaton_str(char *wildcard, char *str)
{
	t_automaton	*oto;
	int			ret;
	int			i;

	i = 0;
	oto = automaton_wildcard_factory(wildcard);
	printf("indexes_of_char \n   ");
	while (++i < oto->cols)
		printf("%2c ", oto->indexes_of_char[i]);
	test_print_transition(oto);
	ret = automaton_validator(oto, str);
	printf("wildcard : {%s}, value : {%s} return : %d\n", wildcard, str, ret);
	automaton_dispose(oto);
}

/**
 * @brief Teste la création d'un automate et affiche son état à l'écran
 * 
 */
void	test_automaton(void)
{
	t_automaton	*oto;
	int			i;

	oto = automaton_factory("tests/automate.conf");
	printf("size\n%d %d \n", oto->cols, oto->rows);
	printf("%d \n", oto->char_indexes['"']);
	i = -1;
	test_print_transition(oto);
	i = -1;
	printf("accepting \n");
	while (++i < oto->rows)
		printf("%d ", oto->accepting[i]);
	automaton_dispose(oto);
	printf("\n\nwild*ard\n");
	oto = automaton_wildcard_factory("wild*ard");
	i = 0;
	printf("indexes_of_char \n   ");
	while (++i < oto->cols)
		printf("%2c ", oto->indexes_of_char[i]);
	test_print_transition(oto);
	automaton_dispose(oto);
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
	automaton_token(&token, oto, input);
	printf("\ninput : %s\n\n", input);
	token_print(token);
	token_dispose(&token);
	automaton_dispose(oto);
	printf("\n\n");
	return (1);
}
