/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 08:51:29 by dthalman          #+#    #+#             */
/*   Updated: 2022/03/09 18:50:32 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief parse une chaine de caractère et retourne
 * une liste de chaine de caractère en fonction du
 * parsing
 *
 * @param shell
 * @return int
 */
int	parse_command_line(t_shell *shell)
{
	t_token		*token;
	t_automaton	*oto;

	oto = automaton_factory(shell->config);
	automaton_token(&token, oto, shell->cmdline);
	sanitize_quotes_token(shell, token);
	//evaluate_str_env_token(token, shell);
	shell->cmds = 0;
	shell->num_cmds = 0;
	if (token)
	{
		prepare_cmds(token, shell);
		wildcard_cmds(shell);
	}
	log_token(token);
	token_dispose(&token);
	automaton_dispose(oto);
	return (shell->num_cmds);
}
