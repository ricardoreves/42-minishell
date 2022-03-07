/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:03 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/07 00:42:10 by rpinto-r         ###   ########.fr       */
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
	char	cwd[256];

	ft_bzero(cwd, sizeof(cwd));
	if (getcwd(cwd, sizeof(cwd)))
		shell->config = str_joins(cwd, CONFIGFILE, "/");
}

void	*init_shell(t_shell *shell, int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	return (ft_memset(shell, 0, sizeof(t_shell)));
}

int	main(int argc, char *argv[], char *envs[])
{
	t_shell	shell;

	if (init_shell(&shell, argc, argv))
	{
		init_asciiart();
		init_signals();
		init_envs(&shell, envs);
		init_config(&shell);
		init_prompt(&shell);
		//while (1)
		// 	sleep(5);
		free(shell.config);
	}
	return (0);
}
