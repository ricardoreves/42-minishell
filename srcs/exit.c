/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 02:06:42 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/12 01:28:28 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_exit(t_shell *shell)
{
	shell->stop = 1;
	ft_putendl_fd("exit", 1);
	free_shell(shell);
	exit(0);
}

void	save_exit_status(t_shell *shell)
{
	if (get_env(shell, "?"))
		set_env(shell, ft_strdup("?"), ft_itoa(shell->exit_status));
	else
		add_env(shell, ft_strdup("?"), ft_itoa(shell->exit_status));
	shell->exit_status = 0;
}
