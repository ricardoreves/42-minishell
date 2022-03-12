/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:29:08 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/11 23:52:32 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Ajoute une commande à la fin de la liste des commandes
 *
 * @param cmd
 * @param cmds
 */
void	push_cmd(t_cmd *cmd, t_cmd **cmds)
{
	t_cmd	*tmp;

	if (!(*cmds))
		*cmds = cmd;
	else
	{
		tmp = *cmds;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cmd;
	}
}

t_cmd	*create_cmd(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	cmd->redirect_id = id_notset;
	push_cmd(cmd, &shell->cmds);
	shell->num_cmds++;
	return (cmd);
}

/**
 * @brief Remplie la liste cmds avec toutes les commandes
 *  a effectué à partir du contenu des jetons crée par le parser.
 *
 * @param token
 * @param cmds
 */
void	prepare_cmds(t_token *token, t_shell *shell)
{
	t_cmd	*cmd;

	cmd = create_cmd(shell);
	while (token)
	{
		if (is_word_token_id(token->id))
		{
			push_array(token->str, &cmd->args);
			if (!cmd->name)
				cmd->name = ft_strdup(token->str);
		}
		else if (is_redirect_token_id(token->id))
		{
			cmd->redirect_id = token->id;
			if (token->next && is_word_token_id(token->next->id))
			{
				token = token->next;
				cmd->redirect_path = ft_strdup(token->str);
			}
		}
		else if (token->id == id_pipe)
			cmd = create_cmd(shell);
		if (token)
			token = token->next;
	}
}

/**
 * @brief Libère la mémoire de la liste des commandes
 * @param cmds
 */
void	free_cmds(t_cmd **cmds)
{
	t_cmd	*last;
	t_cmd	*cmd;

	cmd = *cmds;
	while (cmd)
	{
		last = cmd;
		free(cmd->name);
		free(cmd->redirect_path);
		free_array(cmd->args);
		cmd = cmd->next;
		free(last);
	}
	*cmds = 0;
}
