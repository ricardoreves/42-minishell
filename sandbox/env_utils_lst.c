/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 20:47:22 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/07 17:25:47 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_envlst(t_env **envs)
{
	t_env *tmp;

	while ((*envs))
	{
		tmp = (*envs);
		(*envs) = tmp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

void print_envlst(t_env **envs)
{
	t_env *tmp;

	tmp = (*envs);
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

int init_envslst(t_shell *shell, char *envs[])
{
	int i;
	int j;
	t_env *env;

	i = -1;
	shell->envslst = ft_calloc(sizeof(*env), array_length(envs) + 1);
	while (envs && envs[++i])
	{
		j = 0;
		while (envs[i][j] != 0 && envs[i][j] != '=')
			j++;
		env = new_envlst(str_duplicate_nbytes(envs[i], j), ft_strdup(envs[i] + j + 1));
		// printf("|%s|\n%s %s\n", envs[i], env->name, env->value);
		add_envlst(&shell->envslst, env);
	}
	return (0);
}

t_env *new_envlst(char *name, char *value)
{
	t_env *env;

	env = ft_calloc(sizeof(t_env), 1);
	if (!env)
		return (0);
	env->name = name;
	env->value = value;
	env->next = 0;
	return (env);
}

int add_envlst(t_env **envs, t_env *env)
{
	t_env *tmp;

	if (!env)
		return (0);
	if (!(*envs)->name)
	{
		free((*envs));
		(*envs) = env;
	}
	else
	{
		tmp = (*envs);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = env;
	}
	return (1);
}

t_env *get_envlst(t_env **envs, char *name)
{
	t_env *tmp;

	if (!name || !(*envs))
		return (0);
	tmp = (*envs);
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(name)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

int set_envlst(t_env **envs, char *name, char *value)
{
	t_env *tmp;

	if (!name || !(*envs))
		return (0);
	tmp = (*envs);
	while (tmp)
	{
		if (get_envlst(envs, name))
		{
			free(tmp->value);
			tmp->value = value;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void free_one_envlst(t_env *env)
{
	free(env->value);
	free(env->name);
	free(env);
}

int unset_envlst2(t_env **envs, char *name)
{
	t_env *tmp;
	t_env *prev;

	if (name && (*envs))
	{
		tmp = (*envs);
		prev = 0;
		while (tmp)
		{
			if (ft_strncmp(tmp->name, name, ft_strlen(name)) == 0)
			{
				if (tmp == (*envs))
				{
					(*envs) = tmp->next;
					free_one_envlst(tmp);
					tmp = (*envs);
				}
				else
				{
					prev->next = tmp->next;
					free_one_envlst(tmp);
					tmp = prev->next;
				}
			}
			else
			{
				prev = tmp;
				tmp = tmp->next;
			}
		}
	}
	return (0);
}

int unset_envlst3(t_env **envs, char *name)
{
	t_env *tmp;
	t_env *env;
	t_env *cpy;

	// ft_memset(cpy, 0, sizeof(t_env));
	// cpy->name = 0;
	cpy = new_envlst(0, 0);
	if (name && (*envs))
	{
		tmp = (*envs);
		while (tmp)
		{
			if (ft_strncmp(tmp->name, name, ft_strlen(name)) != 0)
			{
				add_envlst(&cpy, new_envlst(tmp->name, tmp->value));
				// free(tmp->name);
				// free(tmp->value);
			}
			else
			{
			}
			// env = tmp;
			// tmp = env->next;
			///	free_one_envlst(env);
			tmp = tmp->next;
		}
		free_envlst(envs);
		//(*envs) = cpy;
	}
	return (0);
}

int unset_envlst(t_env **envs, char *name)
{
	t_env *tmp;
	t_env *prev;
	t_env *clone;

	if (!name || !(*envs))
		return (0);
	tmp = (*envs);
	prev = (*envs);
	clone = new_envlst(0, 0);
	while (tmp)
	{
		if (get_envlst(envs, name))
			continue;
		add_envlst(&clone, new_envlst(tmp->name, tmp->value));
		//free_one_envlst(prev);
		
		tmp = tmp->next;
	}
	return (0);
}