/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_wildcard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:49:55 by dthalman          #+#    #+#             */
/*   Updated: 2022/03/09 14:17:31 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief traitement des wildcard dans les paramètres des commandes
 * 
 * @param shell 
 */
void	wildcard_cmds(t_shell *shell)
{
	t_cmd	*cmd;
	int		i;
	char	**lists;

	cmd = shell->cmds;
	while (cmd)
	{
		i = -1;
		while (cmd->args && cmd->args[++i])
		{
			if (has_wildcard(cmd->args[i]))
			{
				lists = get_wildcard_files(cmd->args[i], shell);
				if (lists)
				{
					insert_array(lists, cmd->args[i], &cmd->args);
					remove_str_array(cmd->args[i], &cmd->args);
					free_array(lists);
				}
			}
		}
		cmd = cmd->next;
	}
}

/**
 * @brief retourne 1 si la chaine de caractère contient
 * le signe d'un wildcard
 * 
 * @param str 
 * @return int 
 */
int	has_wildcard(char *str)
{
	if (ft_strchr(str, '*') && !ft_strchr(str, '/'))
		return (1);
	return (0);
}

/**
 * @brief Get the wildcard lists object
 * 
 * @param wildcard 
 * @param shell 
 * @return char** 
 */
char	**get_wildcard_files(char *wildcard, t_shell *shell)
{
	char			*pwd;
	DIR				*dir;
	struct dirent	*entry;
	t_automaton		*au;
	char			**lists;

	lists = 0;
	au = automaton_wildcard_factory(wildcard);
	if (!au)
		return (0);
	pwd = get_env(shell, "PWD");
	dir = opendir(pwd);
	if (dir)
	{
		entry = readdir(dir);
		while (entry)
		{
			if (automaton_validator(au, entry->d_name))
				push_array(entry->d_name, &lists);
			entry = readdir(dir);
		}
	}
	closedir(dir);
	automaton_dispose(au);
	return (lists);
}
