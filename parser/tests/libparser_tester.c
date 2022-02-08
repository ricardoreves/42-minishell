/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libparser_tester.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:15:55 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/04 15:15:55 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libparser.h"
#include "libparser_tester.h"
#include <stdlib.h>
#include <stdio.h>

int	main(int __attribute__((unused)) argc, char __attribute__((unused)) **argv)
{
	token_tester("read -p \"Entrez un numéro : \" int1\n");
	token_tester("echo \"out\">>fichier");
	token_tester("commande>fichier");
	token_tester("commande<fichier");
	token_tester("commande|fichier");
	token_tester("commande |fichier");
	token_tester("commande | \"fichier\"");
	token_tester("commande |fichier << test >autre; ls /test/truc && autre");
	token_tester("commande << fichier");
	return (0);
}

void	token_print(t_token *token)
{
	while (token)
	{
		printf("token : %s\n", token->str);
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
	token = ft_parse_token(input);
	token_print(token);
	ft_token_dispose(&token);
	printf("\n\n");
	return (1);
}
