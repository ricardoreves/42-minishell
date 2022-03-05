/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:41:02 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/05 01:05:30 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int put_command_error(t_shell *shell, char *cmd, char *msg, int num)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putendl_fd("", 2);
	shell->exit_status = num;
	return (0);
}

void store_command_error(t_shell *shell)
{
	printf("exit_status: %d %s\n", shell->exit_status, ft_itoa(shell->exit_status));
	if (get_env(shell, "?"))
		set_env(shell, ft_strdup("?"), ft_itoa(shell->exit_status));
	else
		add_env(shell, ft_strdup("?"), ft_itoa(shell->exit_status));
	printf("?: %s\n", get_env(shell, "?"));
	shell->exit_status = 0;
}