/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 02:07:34 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/06 17:12:51 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_export(char **args, char **name, char **value)
{
	size_t i;

	if (!args[1])
		return (0);
	i = 0;
	while (args[1][i] != 0 && args[1][i] != '=')
		i++;
	if (i == ft_strlen(args[1]))
		return (0);
	(*name) = ft_strndup(args[1], i);
	if (!(*name))
		return (0);
	(*value) = ft_strdup(args[1] + i + 1);
	if (!(*value))
		return (0);
	return (1);
}

int execute_export(t_shell *shell, char **args)
{
	char *name;
	char *value;

	if (!parse_export(args, &name, &value))
	{
		printf("export: not a valid identifier\n");
		return (0);
	}
	if (get_env(shell, name))
		return (set_env(shell, name, value));
	else
		return (add_env(shell, name, value));
}