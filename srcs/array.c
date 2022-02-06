/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 20:43:01 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/06 17:13:13 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_array(char *array[])
{
    int i;

    i = 0;
    while (array && array[i])
        printf("%s\n", array[i++]);
}

void free_array(char *array[])
{
    int i;

    i = 0;
    if (array)
    {
        while (array[i])
            free(array[i++]);
        free(array);
    }
}

int array_length(char *array[])
{
    int i;

    i = 0;
    while (array && array[i])
        i++;
    return (i);
}

char **clone_array(char *array[])
{
    int i;
    char **dup;

    i = 0;
    while (array && array[i])
        i++;
    dup = ft_calloc(sizeof(*array), i + 1);
    if (!dup)
        return (0);
    while (i--)
        dup[i] = ft_strdup(array[i]);
    return (dup);
}