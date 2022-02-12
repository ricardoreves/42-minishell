/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 10:42:15 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/10 08:30:42 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libparser.h"

/**
 * @brief retourne vrai si il s'agit d'un caractère de redirection
 * 
 * @param c 
 * @return int 
 */
int	is_redirection(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

/**
 * @brief retourne vrai si il s'agit du caractère pipe
 * 
 * @param c 
 * @return int 
 */
int	is_pipe(int c)
{
	if (c == '|')
		return (1);
	return (0);
}

/**
 * @brief retourne vrai si toute la ligne ne comporte que du vide
 * 
 * @param c 
 * @return int 
 */
int	is_empy_line(char *str)
{
	if (!str)
		return (0);
	while (*str && is_space(*str))
		str++;
	if (!*str)
		return (1);
	return (0);
}

/**
 * @brief retourne vrai si il s'agit du caractère de type digit avec le + et -
 * 
 * @param c 
 * @return int 
 */
int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

/**
 * @brief retourne vrai si le carctère est un caractère d'espace.
 * 
 * @param c 
 * @return int 
 */
int	is_space(int c)
{
	if (c == '\t' || c == '\v' || c == '\n')
		return (1);
	if (c == '\f' || c == ' ' || c == '\r')
		return (1);
	return (0);
}
