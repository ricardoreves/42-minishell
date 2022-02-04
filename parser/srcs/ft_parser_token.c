/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 08:51:29 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/04 17:18:57 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libparser.h"
#include "libft.h"
#include <stdlib.h>

/**
 * @brief Effectue une allocation de mémoire du nombre d'élément nécessaire
 * pour enregitrer tous les jetons
 * 
 * @param str 
 * @param sep liste des caractères qui seront utilisés comme séparateur
 * @param sepcmpt liste des caractères qui seront utilisés comme séparateur
 * @return char** 
 */
int	ft_token_count(char const *str, char *sep, char *sepcmpt)
{
	int	is_sep;
	int	count;

	count = 0;
	is_sep = 1;
	while (*str)
	{
		if (is_sep && !ft_strchr(sep, *str))
		{
			is_sep = 0;
			count++;
		}
		else if (ft_strchr(sep, *str))
		{
			is_sep = 1;
			if (ft_strchr(sepcmpt, *str))
				count++;
		}
		str++;
	}
	return (count);
}

void	ft_move_forward(char const **s, char *sep, int not)
{
	if (not)
	{
		while (**s && !ft_strchr(sep, **s))
			(*s)++;
		if (ft_strchr(SEPARATOR_COUNTED, **s))
			(*s)++;
	}
	else
	{
		while (**s && ft_strchr(sep, **s))
			(*s)++;
	}
}

void	ft_pos_memcpy(char const *start, char const *end, char *mem)
{
	int	x;

	x = 0;
	while (start != end && mem)
	{
		mem[x++] = *start;
		start++;
	}
	mem[x] = 0;
}

char	**ft_parse_token(char  *str)
{
	char const	*start;
	char const	*end;
	char		**token;
	int			count;
	int			y;

	count = ft_token_count(str, SEPARATOR, SEPARATOR_COUNTED);
	token = malloc((count + 1) * sizeof(char *));
	if (!token)
		return (0);
	start = str;
	end = str;
	y = 0;
	while (*end && token)
	{
		ft_move_forward(&start, SEPARATOR, 0);
		end = start;
		ft_move_forward(&end, SEPARATOR, 1);
		if (end - start)
		{
			token[y] = malloc((end - start) + 1);
			ft_pos_memcpy(start, end, token[y++]);
		}
		start = end;
	}
	token[y] = 0;
	return (token);	
}
