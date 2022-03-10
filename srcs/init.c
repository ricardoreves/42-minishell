/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 21:54:07 by dthalman          #+#    #+#             */
/*   Updated: 2022/03/10 15:30:56 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_asciiart(void)
{
	printf("        _       _     \e[0;33m_          _ _ \e[0m\n");
	printf("  /\\/\\ (_)_ __ (_)\e[1;33m___| |__   ___| | |\e[0m\n");
	printf(" /    \\| | '_ \\| \e[0;33m/ __| '_ \\ / _ \\ | |\e[0m\n");
	printf("/ /\\/\\ \\ | | | | \e[0;33m\\__ \\ | | |  __/ | |\e[0m\n");
	printf("\\/    \\/_|_| |_|_\e[0;33m|___/_| |_|\\___|_|_|\e[0m\n");
	printf("\e[0;37mEmbrace the power of the command line ✨\e[0m\n");
	printf("version %s\n\n", VERSION);
	log_message("start " VERSION);
}

void	init_config(t_shell *shell)
{
	shell->workink_dir = malloc(256);
	if (!shell->workink_dir)
		exec_exit(shell);
	if (getcwd(shell->workink_dir, 256))
		shell->config = str_joins(shell->workink_dir, CONFIGFILE, "/");
	handle_echoctl();
}

void	*init_shell(t_shell *shell, int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	return (ft_memset(shell, 0, sizeof(t_shell)));
}

t_shell	*get_shell(void)
{
	static t_shell	shell;

	return (&shell);
}
