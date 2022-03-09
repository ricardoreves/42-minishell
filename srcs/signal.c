/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:58:20 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/09 23:04:39 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_echoctl(void)
{
	struct termios	termios_new;
	struct termios	termios_save;

	if (tcgetattr(0, &termios_save))
	{
		perror("Error: tcgetattr() failed");
		exit(1);
	}
	termios_new = termios_save;
	termios_new.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &termios_new))
	{
		perror("Error: tcsetattr() failed");
		exit(1);
	}
}

void	handle_signals(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
	}
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
	}
}

void	handle_signals_redisplay(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	init_signals(int redisplay)
{
	if (redisplay)
	{
		signal(SIGQUIT, handle_signals_redisplay);
		signal(SIGINT, handle_signals_redisplay);
	}
	else
	{
		signal(SIGQUIT, handle_signals);
		signal(SIGINT, handle_signals);
	}
}
