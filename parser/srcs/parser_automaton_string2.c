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
 * @brief Ajout dans la colonne de la transition les enregistrement pour les
 * caractère *
 * 
 * @param str 
 * @param row 
 * @param au 
 */
void	auto_load_str_transitions_star(char *str, int row, t_automaton *au)
{
	int	col;

	col = -1;
	while (++col < au->cols)
	{
		au->transitions[col + (row * au->cols)] = row;
		if (au->indexes_of_char[col] == *str)
			au->transitions[col + (row * au->cols)] = row + 1;
	}
}

/**
 * @brief Ajout dans la colonne de la transition les enregistrement pour tous
 * les autres caractères
 * 
 * @param str 
 * @param row 
 * @param au 
 */
void	auto_load_str_transitions_other(char *str, int row, t_automaton *au)
{
	int	col;

	col = -1;
	while (++col < au->cols)
	{
		if (row < au->rows - 1)
		{
			if (au->indexes_of_char[col] == *str)
				au->transitions[col + (row * au->cols)] = row + 1;
		}
	}
}

/**
 * @brief Crée les étapes de transition selon la chaine de caractère
 * 
 * @param str 
 * @param au 
 */
void	auto_load_str_transitions(char *str, t_automaton *au)
{
	int		row;
	int		col;

	row = -1;
	while (++row < au->rows)
	{
		col = -1;
		while (++col < au->cols)
			au->transitions[col + (row * au->cols)] = 99;
	}
	row = -1;
	while (*str && ++row < au->rows)
	{
		if (*str == '*')
		{
			while (*str == '*')
				str++;
			auto_load_str_transitions_star(str, row, au);
		}
		else
			auto_load_str_transitions_other(str, row, au);
		str++;
	}
	++row;
	auto_load_str_transitions_other(str, row, au);
}
