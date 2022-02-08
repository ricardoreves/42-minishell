/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:40:30 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/08 15:06:07 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_varenv_value(t_shell *shell, char *str, int *i)
{
    int j;
    char name[256];

    j = 0;
    ft_bzero(name, sizeof(name));
    while (ft_isalnum(str[j]) || str[j] == '_')
    {
        name[j] = str[j];
        (*i)++;
        j++;
    }
    return (get_env(shell, name));
}

char *eval_varenv_str(t_shell *shell, char *str, int k)
{
    int i;
    int j;
    char *eval;
    char *value;

    i = 0;
    j = 0;
    eval = ft_calloc(sizeof(char), 4096);
    while (str && str[i])
    {
        if (str[i] == '$' && !ft_isdigit(str[i + 1]))
        {
            i++;
            k = 0;
            value = get_varenv_value(shell, str + i, &i);
            while (value && value[k])
                eval[j++] = value[k++];
        }
        else
            eval[j++] = str[i++];
    }
    return (eval);
}

char **eval_varenv_map(t_shell *shell, char *arr[])
{
    int i;
    char **tmp;

    i = -1;
    tmp = ft_calloc(sizeof(char *), array_length(arr) + 1);
    while (arr && arr[++i])
        tmp[i] = eval_varenv_str(shell, arr[i], 0);
    free_array(arr);
    return (tmp);
}