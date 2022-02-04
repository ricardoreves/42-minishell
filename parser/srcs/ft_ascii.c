/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ascii.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 10:42:15 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/04 10:42:15 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libparser.h"

/**
 * @brief retourne vrai si il s'agit d'un caractère de redirection
 * 
 * @param c 
 * @return int 
 */
int	ft_is_redirection(int c)
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
int	ft_is_pipe(int c)
{
	if (c == '|')
		return (1);
	return (0);
}

/**
 * @brief retourne vrai si il s'agit du caractère &
 * 
 * @param c 
 * @return int 
 */
int	ft_is_and(int c)
{
	if (c == '&')
		return (1);
	return (0);
}

/**
 * @brief retourne vrai si il s'agit du caractère ; (end of expression)
 * 
 * @param c 
 * @return int 
 */
int	ft_is_eoe(int c)
{
	if (c == '&')
		return (1);
	return (0);
}
