/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:03 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/09 21:54:25 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envs[])
{
	t_shell	shell;

	if (init_shell(&shell, argc, argv))
	{
		init_asciiart();
		init_envs(&shell, envs);
		init_config(&shell);
		init_prompt(&shell);
		free_shell(&shell);
		//while (1)
		// 	sleep(5);
	}
	return (0);
}
