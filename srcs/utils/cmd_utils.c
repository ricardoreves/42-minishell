/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:29:08 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/28 18:50:56 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *create_cmd(void)
{
	t_cmd *cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	cmd->redirect = id_notset;
	return (cmd);
}

/**
 * @brief Ajoute une commande à la fin de la liste des commandes
 *
 * @param cmd
 * @param cmds
 */
void push_cmd(t_cmd *cmd, t_cmd **cmds)
{
	t_cmd *tmp;

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

/**
 * @brief Remplie la liste cmds avec toutes les commandes
 *  a effectué à partir du contenu des jetons crée par le parser.
 *
 * @param token
 * @param cmds
 */
void prepare_cmds(t_token *token, t_cmd **cmds)
{
	t_cmd *cmd;

	cmd = create_cmd();
	push_cmd(cmd, cmds);
	while (token)
	{
		if (is_word(token->id))
		{
			push_array(token->str, &cmd->args);
			if (!cmd->name)
				cmd->name = ft_strdup(token->str);
		}
		else if (is_redirect(token->id))
		{
			cmd->redirect = token->id;
			token = token->next;
			if (token)
				cmd->filename = ft_strdup(token->str);
		}
		else if (token->id == id_pipe)
		{
			cmd = create_cmd();
			push_cmd(cmd, cmds);
		}
		token = token->next;
	}
}

/**
 * @brief Affiche le contenu de la liste des commandes
 * @param cmds
 */
void print_cmds(t_cmd *cmds)
{
	int i;
	t_cmd *cmd;

	i = -1;
	cmd = cmds;
	while (cmd)
	{
		printf("commande:\n");
		printf("name: %s\n", cmd->name);
		// print_array(cmd->args);
		while (cmd->args && cmd->args[++i])
			printf("arg[%d]: %s\n", i, cmd->args[i]);
		printf("redirect: %d\n", cmd->redirect);
		printf("filename: %s\n", cmd->filename);
		printf("---------------\n");
		cmd = cmd->next;
	}
}

/**
 * @brief Compte le nombre de commandes
 * @param cmds
 */
int count_cmds(t_cmd *cmds)
{
	int i;
	t_cmd *cmd;

	if (!cmds)
		return (0);
	i = 0;
	cmd = cmds;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}