/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tester.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 21:41:03 by dthalman          #+#    #+#             */
/*   Updated: 2022/03/09 22:21:13 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief effectue les différents tests de validité du minishell
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int	main(int __attribute__((unused)) argc, char __attribute__((unused)) **argv, char *envs[])
{
	t_shell	shell;
	char 	*file;

	if (init_shell(&shell, argc, argv))
	{
		init_envs(&shell, envs);
		init_config(&shell);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);	
		printf("start\n");
		file = get_tempfilename(&shell);
		printf("test new tempfile : %s\n", file);
		free(file);
		free_shell(&shell);
	}
	return (0);
}
