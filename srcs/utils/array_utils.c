/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 20:43:01 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/07 19:17:10 by rpinto-r         ###   ########.fr       */
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