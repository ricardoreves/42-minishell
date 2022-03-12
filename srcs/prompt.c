/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 00:45:42 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/12 01:28:51 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt_name(t_shell *shell)
{
	char	*prompt;

	prompt = get_env(shell, "PWD");
	if (!prompt)
		prompt = ft_strjoin(NAME, DOLLAR);
	else
		prompt = str_joins(NAME, DOLLAR, get_env(shell, "PWD"));
	return (prompt);
}

void	init_prompt(t_shell *shell)
{
	char	*prompt;

	while (!shell->stop)
	{
		init_signals(1);
		prompt = get_prompt_name(shell);
		shell->cmdline = readline(prompt);
		if (!shell->cmdline)
			exec_exit(shell);
		else if (*shell->cmdline)
		{
			init_signals(0);
			add_history(shell->cmdline);
			if (parse_command_line(shell))
			{
				if (is_valid_commands(shell))
					exec_commands(shell);
				free_cmds(&(shell->cmds));
			}
			else
				show_command_error(shell, NULL, MSG_SYNTAX_ERROR, 2);
		}
		free(shell->cmdline);
		free(prompt);
	}
}
