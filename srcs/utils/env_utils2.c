/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:40:30 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/05 22:35:48 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contain_env(char *str, char *name)
{
	char	*tmp;

	if (!str || !name)
		return (0);
	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (0);
	if (ft_strncmp(str, tmp, ft_strlen(tmp)) == 0)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

char	*get_evaluate_value(t_shell *shell, char *str, int *i)
{
	int		j;
	char	name[256];

	j = 0;
	ft_bzero(name, sizeof(name));
	while (ft_isalnum(str[j]) || str[j] == '_' || str[j] == '?')
	{
		name[j] = str[j];
		(*i)++;
		j++;
	}
	return (get_env(shell, name));
}

char	*evaluate_str_env(t_shell *shell, char *str, int k)
{
	int		i;
	int		j;
	char	*str2;
	char	*value;

	i = 0;
	j = 0;
	str2 = ft_calloc(sizeof(char), 4096);
	while (str && str[i] && i < 4096)
	{
		if (str[i] == '$' && !ft_isdigit(str[i + 1]))
		{
			i++;
			k = 0;
			value = get_evaluate_value(shell, str + i, &i);
			while (value && value[k])
				str2[j++] = value[k++];
		}
		else
			str2[j++] = str[i++];
	}
	return (str2);
}
