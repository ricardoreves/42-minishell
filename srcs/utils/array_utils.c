/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 20:43:01 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/26 14:33:37 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_array(char *arr[])
{
    int i;

    i = 0;
    while (arr && arr[i])
        printf("%s\n", arr[i++]);
}

void free_array(char *arr[])
{
    int i;

    i = 0;
    if (arr)
    {
        while (arr[i])
            free(arr[i++]);
        free(arr);
    }
}

int array_length(char *arr[])
{
    int i;

    i = 0;
    while (arr && arr[i])
        i++;
    return (i);
}

char **clone_array(char *arr[])
{
    int i;
    char **dup;

    i = 0;
    while (arr && arr[i])
        i++;
    dup = ft_calloc(sizeof(*arr), i + 1);
    if (!dup)
        return (0);
    while (i--)
        dup[i] = ft_strdup(arr[i]);
    return (dup);
}

void	push_array(char *str, char ***arr)
{
	char	**new_arr;
	int		len;
	int		i;

	len = array_length(*arr);
	new_arr = ft_calloc(sizeof(char**), len + 2);
    if (!new_arr)
        return ;
	i = 0;
    while (*arr && *arr[i])
	{
		new_arr[i] = *arr[i];
		i++;
	}
	new_arr[i] = ft_strdup(str);
	new_arr[i + 1] = NULL;
	free(*arr);
	*arr = new_arr;
}