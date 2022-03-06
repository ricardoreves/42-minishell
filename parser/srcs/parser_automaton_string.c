/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_automaton_string.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 10:55:31 by dthalman          #+#    #+#             */
/*   Updated: 2022/03/06 08:52:35 by dthalman         ###   ########.fr       */
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
	char	*str;
	char	*line;

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
	char	*str;

	idx = 0;
	while (str && *str)
	{
		if (*str < CHAR_INDEXES_LEN && idx < au->cols)
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
	char	*str;

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

void	auto_load_accepting(int fd, t_automaton *au)
{
	int		v;
	int		idx;
	char	*str;

	idx = -1;
	str = read_ignore_comment(fd);
	while (str && *str && ++idx < au->rows)
	{
		v = ft_atoi(str);
		while (*str && is_space(*str))
			str++;
		while (*str && is_digit(*str))
			str++;
		while (*str && is_space(*str))
			str++;
		au->accepting[idx] = v;
		if (!is_space(*str) && !is_digit(*str))
			break ;
	}
}

int	get_char_index(const int c, t_automaton *au)
{
	if (c < 0 || c > CHAR_INDEXES_LEN - 1 || !au->char_indexes)
		return (0);
	else
		return (au->char_indexes[c]);
}
