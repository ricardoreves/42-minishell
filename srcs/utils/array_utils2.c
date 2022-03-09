/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 07:52:03 by dthalman          #+#    #+#             */
/*   Updated: 2022/03/09 08:13:29 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief insert un tableau dans un autre tableau de chaine de caractère
 * après la position de after
 * 
 * @param new_arr 
 * @param after 
 * @param arr 
 */
void	insert_array(char **new_arr, char *after, char ***arr)
{
	int		i;
	char	**tmp;
	char	**next;
	int		new_len;

	new_len = array_length(new_arr) + array_length(*arr) + 1;
	tmp = ft_calloc(sizeof(char **), new_len + 1);
	next = *arr;
	i = -1;
	while (*next)
	{
		tmp[++i] = ft_strdup(*next);
		if (*next == after)
		{
			while (*new_arr)
			{
				tmp[++i] = ft_strdup(*new_arr);
				new_arr++;
			}	
		}
		next++;
	}
	tmp[++i] = 0;
	free_array(*arr);
	(*arr) = tmp;
}