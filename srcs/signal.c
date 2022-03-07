/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:58:20 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/07 15:45:10 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_signals(int signum)
{
	if (signum == SIGINT)
	{
		ft_putendl_fd("", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	//printf("signum: %d\n", signum);
	//if (signum == SIGSEGV)
	//{
	//	kill(getpid(), SIGTERM);
	//}
}

void init_signals(void)
{
	// signal(SIGTERM, handle_signals);
	// signal(SIGSTOP, handle_signals);
	// signal(SIGKILL, handle_signals);
	// signal(SIGSEGV, handle_signals);
	// signal(SIGABRT, handle_signals);
	signal(SIGQUIT, handle_signals);
	signal(SIGINT, handle_signals);
	//signal(SIGQUIT, SIG_IGN);
}
