/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 08:51:29 by dthalman          #+#    #+#             */
/*   Updated: 2022/03/02 00:46:59 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief remplace les variables d'environnment et identifie si
 * c'est un executable
 *
 * @param token
 * @param shell
 */
void evaluate_str_env_token(t_token *token, t_shell *shell)
{
	t_token *t;
	char *str;

	t = token;
	while (t)
	{
		if (t->id == id_word || t->id == id_dbl_quotes || t->id == id_single_quotes)
		{
			str = evaluate_str_env(shell, t->str, 0);
			free(t->str);
			t->str = str;
			set_builtin_token_id(t);
		}
		t = t->next;
	}
}

/**
 * @brief identifie les jetons de type builtin
 *
 * @param token
 */
void set_builtin_token_id(t_token *token)
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
int is_word_token_id(int id)
{
	return (is_builtin_token_id(id) || id == id_word);
}

/**
 * @brief Vérifie si l'id est de type redirection
 *
 * @param id
 * @return int
 */
int is_redirect_token_id(int id)
{
	if (id == id_out_write)
		return (1);
	if (id == id_out_append)
		return (1);
	if (id == id_in_file)
		return (1);
	if (id == id_in_std)
		return (1);
	return (0);
}

/**
 * @brief vérifie si l'id est de type builtin
 *
 * @param id
 * @return int
 */
int is_builtin_token_id(int id)
{
	if (id == id_builtin_cd)
		return (1);
	if (id == id_builtin_echo)
		return (1);
	if (id == id_builtin_env)
		return (1);
	if (id == id_builtin_exit)
		return (1);
	if (id == id_builtin_export)
		return (1);
	if (id == id_builtin_pwd)
		return (1);
	if (id == id_builtin_unset)
		return (1);
	return (0);
}