/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 21:40:07 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/02 03:07:36 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_echo(t_shell *shell, t_cmd *cmd)
{
	int i;
	int size;
	(void)shell;

	i = 1;
	size = array_length(cmd->args);
	if (size > 1)
	{
		while (cmd->args && cmd->args[i])
		{
			ft_putstr_fd(cmd->args[i], 1);
			i++;
			if (i < size)
				ft_putstr_fd(" ", 1);
		}
		if (str_compare(cmd->args[1], "-n") != 0)
			ft_putendl_fd("", 1);
	}
	else
		ft_putendl_fd("", 1);
	return (0);
}

/*
echo (nl)
echo -n (none)
echo hello (text + nl)
echo -n hello (text)
echo "welcome to $HOME"
echo -n "welcome to $HOME"
echo -n -n (none)
 */