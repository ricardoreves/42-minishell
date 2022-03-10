/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:03 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/10 02:09:52 by rpinto-r         ###   ########.fr       */
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
	}
	return (0);
}
