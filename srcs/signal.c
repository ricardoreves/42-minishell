/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:58:20 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/07 18:13:24 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void	handle_echoctl(void)
{
	int				ret;
    struct termios	termios_new;
	struct termios	termios_save;

    ret = tcgetattr(0, &termios_save);
    if (ret)
    {
        perror("Error: tcgetattr() failed");
        exit(1);
    }
    termios_new = termios_save;
    termios_new.c_lflag &= ~ECHOCTL;
    ret = tcsetattr(0, 0, &termios_new);
	if (ret)
    {
        perror("Error: tcsetattr() failed");
        exit(1);
    }
}

void	handle_signals(int signum)
{
	handle_echoctl();
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
	}
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("",1);
	}
}

void	handle_signals_redisplay(int signum)
{   
	handle_echoctl();
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
		rl_replace_line("",1);
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
