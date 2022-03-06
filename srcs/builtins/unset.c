/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 02:07:49 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/06 04:33:46 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_unset(t_shell *shell, t_cmd *cmd)
{
	if (cmd->args && cmd->args[1])
		unset_env(shell, cmd->args[1]);
	return (0);
}
