/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:18:01 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/09 15:59:58 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell)
{
	if (shell->cmds)
		free_cmds(shell->cmds);
	if (shell->envs)
		free_array(shell->envs);
	if (shell->config)
		free(shell->config);
	shell->cmds = 0;
	shell->envs = 0;
	shell->config = 0;
	shell = 0;
}

/**
 * @brief Libère la mémoire de la liste des commandes
 * @param cmds
 */
void	free_cmds(t_cmd *cmd)
{
	t_cmd	*last;

	while (cmd)
	{
		last = cmd;
		free(cmd->name);
		free(cmd->redirect_path);
		free_array(cmd->args);
		cmd = cmd->next;
		free(last);
	}
}

void	free_pipes(int **pipes, int size)
{
	if (pipes && size)
	{
		while (size--)
			free(pipes[size]);
		free(pipes);
	}
}
