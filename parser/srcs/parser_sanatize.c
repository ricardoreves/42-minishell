/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sanatize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 08:51:29 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/23 08:20:27 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libparser.h"
#include "libft.h"
#include <stdlib.h>

/**
 * @brief supprime les guillements de la liste
 * 
 * @param token 
 */
void	sanatize_quotes_token(t_token *token)
{
	t_token	*t;
	int		i;
	int		len;	

	t = token;
	while (t)
	{
		if (t->id == id_dbl_quotes || t->id == id_single_quotes)
		{
			len = ft_strlen(t->str);
			i = 0;
			while (i < len - 2)
			{
				t->str[i] = t->str[i + 1];
				i++;
			}
			t->str[i] = '\0';
		}
		t = t->next;
	}
}
