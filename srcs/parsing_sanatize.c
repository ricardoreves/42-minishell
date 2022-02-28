/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sanatize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 08:51:29 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/28 03:33:06 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Supprime les guillements d'un element de la liste
 *
 * @param t
 */
void sanatize_quotes_word_token(t_token *t)
{
	int len;
	int i;
	int decal;

	len = ft_strlen(t->str);
	i = -1;
	decal = 0;
	while (++i < len - decal)
	{
		if (t->str[i + decal] == '\'' || t->str[i + decal] == '"')
			decal++;
		t->str[i] = t->str[i + decal];
	}
	t->str[i] = '\0';
}

/**
 * @brief supprime les guillements de toute la liste
 *
 * @param token
 */
void sanatize_quotes_token(t_token *token)
{
	t_token *t;

	t = token;
	while (t)
	{
		if (t->id == id_dbl_quotes || t->id == id_single_quotes)
		{
			sanatize_quotes_word_token(t);
		}
		if (t->id == id_word)
		{
			sanatize_quotes_word_token(t);
		}
		t = t->next;
	}
}

/**
 * @brief remplace les variables d'environnment et identifie si
 * c'est un executable
 *
 * @param token
 * @param shell
 */
void exec_ident_token(t_token *token, t_shell *shell)
{
	t_token *t;
	char *str;

	t = token;
	while (t)
	{
		if (t->id == id_word || t->id == id_dbl_quotes || t->id == id_single_quotes)
		{
			str = eval_varenv_str(shell, t->str, 0);
			free(t->str);
			t->str = str;
			set_token_builtin(t);
		}
		t = t->next;
	}
}

/**
 * @brief identifie les jetons de type builtin
 *
 * @param token
 */
void set_token_builtin(t_token *token)
{
	if (str_compare(token->str, "cd") == 0)
		token->id = id_builtin_cd;
	else if (str_compare(token->str, "echo") == 0)
		token->id = id_builtin_echo;
	else if (str_compare(token->str, "env") == 0)
		token->id = id_builtin_env;
	else if (str_compare(token->str, "exit") == 0)
		token->id = id_builtin_exit;
	else if (str_compare(token->str, "export") == 0)
		token->id = id_builtin_export;
	else if (str_compare(token->str, "pwd") == 0)
		token->id = id_builtin_pwd;
	else if (str_compare(token->str, "unset") == 0)
		token->id = id_builtin_unset;
}

/**
 * @brief Vérifie si l'id est un mot
 *
 * @param id
 * @return int
 */
int is_word(int id)
{
	if (is_id_builtin(id) || id == id_word)
		return (1);
	else
		return (0);
}

/**
 * @brief Vérifie si l'id est de type redirection
 *
 * @param id
 * @return int
 */
int is_redirect(int id)
{
	if (id == id_out_write || id == id_out_append || id == id_in_file || id == id_in_std)
		return (1);
	else
		return (0);
}

/**
 * @brief vérifie si l'id est de type builtin
 *
 * @param id
 * @return int
 */
int is_id_builtin(int id)
{
	if (id == id_builtin_cd || id == id_builtin_echo || id == id_builtin_env || id == id_builtin_exit || id == id_builtin_export || id == id_builtin_pwd || id == id_builtin_unset)
		return (1);
	else
		return (0);
}

/**
 * @brief Get the last cmd object
 *
 * @param cmd
 * @return t_cmd*
 */
t_cmd *get_last_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

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
 * @param new_cmd
 * @param cmds
 */
void push_cmd(t_cmd *new_cmd, t_cmd **cmds)
{
	t_cmd *last_cmd;

	if (!(*cmds))
	{
		*cmds = new_cmd;
	}
	else
	{
		last_cmd = get_last_cmd(*cmds);
		last_cmd->next = new_cmd;
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
	//char **args;
	//int i;

	//i = 0;
	//args = 0;
	cmd = create_cmd();
	push_cmd(cmd, cmds);
	cmd->args = 0;
	while (token)
	{
		if (is_word(token->id))
		{
			//printf(">>%s\n", token->str);
			push_array(token->str, &cmd->args);
			if (!cmd->name)
				cmd->name = ft_strdup(token->str);
			//print_array(cmd->args);
			// if (new_cmd->args && *(new_cmd->args) && !new_cmd->name)
			//	new_cmd->name = ft_strdup(*(new_cmd->args));
			// i++;
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
		//print_array(cmd->args);
		while (cmd->args && cmd->args[++i])
			printf("arg[%d]: %s\n", i, cmd->args[i]);
		printf("redirect: %d\n", cmd->redirect);
		printf("filename: %s\n", cmd->filename);
		printf("---------------\n");
		cmd = cmd->next;
	}
}

/**
 * @brief Libère la mémoire de la liste des commandes
 * @param cmds
 */
void free_cmds(t_cmd *cmds)
{
	t_cmd *cmd;

	if (!cmds)
		return;
	cmd = cmds;
	while (cmd)
	{
		free(cmd->name);
		free(cmd->filename);
		free_array(cmd->args);
		cmd = cmd->next;
	}
	free(cmds);
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