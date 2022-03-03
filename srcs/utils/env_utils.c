/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 20:47:22 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/03 00:58:00 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int contain_env(char *str, char *name)
{
	char *tmp;

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

int add_env(t_shell *shell, char *name, char *value)
{
	int i;
	char **envs;

	if (!name || !value)
		return (0);
	i = array_length(shell->envs);
	envs = ft_calloc(sizeof(*envs), i + 2);
	if (!envs)
		return (0);
	envs[i] = str_joins(name, value, "=");
	while (i--)
		envs[i] = shell->envs[i];
	free(name);
	free(value);
	free(shell->envs);
	shell->envs = envs;
	return (1);
}

char *get_env(t_shell *shell, char *name)
{
	int i;

	i = -1;
	if (!name)
		return (0);
	while (shell->envs[++i])
		if (contain_env(shell->envs[i], name))
			return (shell->envs[i] + ft_strlen(name) + 1);
	return (0);
}

int set_env(t_shell *shell, char *name, char *value)
{
	int i;

	i = -1;
	if (!name || !value)
		return (0);
	while (shell->envs[++i])
	{
		if (contain_env(shell->envs[i], name))
		{
			free(shell->envs[i]);
			shell->envs[i] = str_joins(name, value, "=");
		}
	}
	free(name);
	free(value);
	return (1);
}

int unset_env(t_shell *shell, char *name)
{
	int i;
	int j;
	char **envs;

	i = -1;
	j = -1;
	if (!name || !get_env(shell, name))
		return (0);
	envs = ft_calloc(sizeof(*envs), array_length(shell->envs));
	if (!envs)
		return (0);
	while (shell->envs[++i])
		if (contain_env(shell->envs[i], name) == 0)
			envs[++j] = ft_strdup(shell->envs[i]);
	free_array(shell->envs);
	shell->envs = envs;
	return (1);
}

int init_envs(t_shell *shell, char *envs[])
{
	int i;

	if (!envs)
		return (0);
	i = array_length(envs);
	shell->envs = ft_calloc(sizeof(*envs), i + 1);
	if (!shell->envs)
		return (0);
	while (i--)
		shell->envs[i] = ft_strdup(envs[i]);
	return (1);
}
