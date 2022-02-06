/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 20:47:22 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/06 18:17:36 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	envs[i] = ft_strsjoin(name, value, "=");
	while (i--)
		envs[i] = ft_strdup(shell->envs[i]);
	free(name);
	free(value);
	free_array(shell->envs);
	shell->envs = envs;
	return (1);
}

char *get_env(t_shell *shell, char *name)
{
	int i;
	int size;
	char *tmp;

	i = -1;
	if (!name)
		return (0);
	tmp = ft_strjoin(name, "=");
	size = ft_strlen(tmp);
	while (shell->envs[++i])
	{
		if (ft_strncmp(shell->envs[i], tmp, size) == 0)
		{
			free(tmp);
			return (shell->envs[i] + size);
		}
	}
	free(tmp);
	return (0);
}

int set_env(t_shell *shell, char *name, char *value)
{
	int i;
	char *tmp;

	if (!name || !value)
		return (0);
	i = -1;
	tmp = ft_strjoin(name, "=");
	while (shell->envs[++i])
	{
		if (ft_strncmp(shell->envs[i], tmp, ft_strlen(tmp)) == 0)
		{
			free(shell->envs[i]);
			shell->envs[i] = ft_strsjoin(name, value, "=");
		}
	}
	free(name);
	free(value);
	free(tmp);
	return (1);
}

int unset_env(t_shell *shell, char *name)
{
	int i;
	int j;
	char *tmp;
	char **envs;

	i = -1;
	j = -1;
	if (!name || !get_env(shell, name))
		return (0);
	tmp = ft_strjoin(name, "=");
	envs = ft_calloc(sizeof(*envs), array_length(shell->envs));
	if (!tmp || !envs)
		return (0);
	while (shell->envs[++i])
		if (ft_strncmp(shell->envs[i], tmp, ft_strlen(tmp)) != 0)
			envs[++j] = ft_strdup(shell->envs[i]);
	free(tmp);
	free_array(shell->envs);
	shell->envs = envs;
	return (1);
}

int init_envs(t_shell *shell, char *envs[])
{
	int i;

	i = array_length(envs);
	shell->envs = ft_calloc(sizeof(*envs), i + 1);
	if (!shell->envs)
		return (0);
	while (i--)
		shell->envs[i] = ft_strdup(envs[i]);
	return (1);
}
