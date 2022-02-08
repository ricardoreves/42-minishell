/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 20:43:01 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/07 18:40:48 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *str_joinsep(char *str1, char *str2, char *sep)
{
    char *str;
    char *tmp;

    if (!str1 || !str2)
        return (0);
    tmp = ft_strjoin(str1, sep);
    if (!tmp)
        return (0);
    str = ft_strjoin(tmp, str2);
    free(tmp);
    if (!str)
        return (0);
    return (str);
}

char *str_duplicate_nbytes(char *str1, size_t n)
{
    size_t i;
    char *dup;

    if (!str1 || n < 1)
        return (0);
    dup = ft_calloc(sizeof(char), n + 1);
    if (!dup)
        return (0);
    i = -1;
    while (++i < n)
        dup[i] = str1[i];
    return (dup);
}

int str_compare(char *str1, char *str2)
{
    return (ft_strncmp(str1, str2, ft_strlen(str2)));
}