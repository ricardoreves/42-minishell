/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_automaton_string.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 10:55:31 by dthalman          #+#    #+#             */
/*   Updated: 2022/03/06 09:09:54 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libparser.h"
#include "parser_automaton.h"
#include "libft.h"

/**
 * @brief charge la taille de l'automate en fonction de la
 * chaine
 * 
 * @param str 
 * @param au 
 */
void	auto_load_str_size(char *str, t_automaton *au)
{
	au->cols = count_char_in_str(str) + 2;
	au->rows = ft_strlen(str) - count_char_of(str, '*') + 2;
}

/**
 * @brief compte le nombre de caractère c contenu dans la chaine
 * 
 * @param str 
 * @param c 
 * @return int 
 */
int	count_char_of(char *str, char c)
{
	int	count;

	count = 0;
	while (str && *str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

/**
 * @brief compte le nombre de caractère contenu dans la chaine
 * 
 * @param str 
 * @return int 
 */
int	count_char_in_str(char *str)
{
	int	count;
	int	i;
	int	y;
	int	found;

	count = 0;
	i = -1;
	while (str && str[++i])
	{
		found = 0;
		y = i;
		while (--y > -1)
		{
			if (str[i] == str[y])
				found = 1;
		}
		if (!found)
			count++;
	}
	return (count);
}

/**
 * @brief charge l'indexe des chaines de caractères dans l'automate
 * 
 * @param str 
 * @param au 
 */
void	auto_load_str_indexes(char *str, t_automaton *au)
{
	int		c;
	int		idx;

	au->indexes_of_char = ft_calloc(sizeof(char), au->cols);
	au->indexes_of_char[0] = (char)255;
	idx = 0;
	c = 0;
	while (str && *str)
	{
		if (idx < au->cols)
		{
			c = *str;
			if (au->char_indexes[c] == 0)
			{
				idx++;
				au->char_indexes[c] = idx;
				au->indexes_of_char[idx] = c;
			}
		}
		str++;
	}
	idx++;
	au->char_indexes[0] = idx;
	au->indexes_of_char[idx] = 0;
}

/**
 * @brief spécifie l'état d'acception pour la chaine de caractère
 * 
 * @param au 
 */
void	auto_load_str_accepting(t_automaton *au)
{
	au->accepting[au->rows - 1] = 1;
}
