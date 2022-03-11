/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 00:45:42 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/11 17:41:05 by rpinto-r         ###   ########.fr       */
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
					handle_commands(shell);
				free_cmds(&(shell->cmds));
			}
			else
				show_command_error(shell, NAME, MSG_SYNTAX_ERROR, 2);
		}
		free(shell->cmdline);
		free(prompt);
	}
}

void	scan_stdin(t_cmd *cmd)
{
	char	*line;

	while (1)
	{
		line = readline(">\n");
		if (*line)
			break ;
		else
			free(line);
	}
	cmd->name = line;
	cmd->args = ft_split(line, ' ');
}

/**
 * @brief contrôle que les commandes sont correctement formaté
 * 
 * @param shell 
 * @return int 
 */
int	is_valid_commands(t_shell *shell)
{
	if (is_unexpected_token_command(shell))
		return (0);
	if (!is_valid_heredoc(shell))
		return (0);
	return (1);
}

