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
	au->cols = count_char_in_str(str) + 1;
	au->rows = au->cols;
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

	idx = 0;
	c = 0;
	while (str && *str)
	{
		if (idx < au->cols)
		{
			if (au->char_indexes[c] == 0)
			{
				idx++;
				au->char_indexes[c] = idx;
			}
		}
		str++;
	}
}

void	auto_load_str_transitions(char *str, t_automaton *au)
{
	int		row;
	int		col;

	row = -1;
	while (++row < au->rows)
	{
		col = -1;
		while (str && *str && ++col < au->cols)
		{
			if (*str == '*')
			{

			}
			else
			{

			}
			au->transitions[col + (row * au->cols)] = ft_atoi(str);
			while (*str && is_space(*str))
				str++;
			while (*str && is_digit(*str))
				str++;
			while (*str && is_space(*str))
				str++;
			if (!is_space(*str) && !is_digit(*str))
				break ;
		}
	}
}