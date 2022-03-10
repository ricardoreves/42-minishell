/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:58:20 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/10 15:30:00 by rpinto-r         ###   ########.fr       */
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
	t_shell	*shell;

	shell = get_shell();
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		shell->exit_status = 1;
		save_exit_status(shell);
	}
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
	}
}

void	handle_signals_redisplay(int signum)
{
	t_shell	*shell;

	shell = get_shell();
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		shell->exit_status = 1;
		save_exit_status(shell);
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
