/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 20:43:01 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/28 02:57:37 by rpinto-r         ###   ########.fr       */
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
    char **clone;

    i = 0;
    while (arr && arr[i])
        i++;
    clone = ft_calloc(sizeof(*arr), i + 1);
    if (!clone)
        return (0);
    while (i--)
        clone[i] = ft_strdup(arr[i]);
    return (clone);
}

void push_array(char *str, char ***arr)
{
    int i;
    char **tmp;

    i = 0;
    while ((*arr) && (*arr)[i])
        i++;
    tmp = ft_calloc(sizeof(char **), i + 2);
    if (!tmp)
        return;
    tmp[i] = ft_strdup(str);
    tmp[i + 1] = 0;
    while (i--)
        tmp[i] = ft_strdup((*arr)[i]);
    free_array((*arr));
    (*arr) = tmp;
}