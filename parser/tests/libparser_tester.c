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
	tocken_tester();
	return (0);
}

/**
 * @brief vérfication de la génération de jeton
 * 
 * @return int 
 */
int	tocken_tester(void)
{
	// char	**ret;
	char	*input;
	int		count;
	int		value;

	input = "une commande | de ouf >> test";
	value = 8;
	count = ft_token_count(input, SEPARATOR, SEPARATOR_COUNTED);
	printf("%d, %d\n", count, value);
	// free(ret);
	return (1);
}
