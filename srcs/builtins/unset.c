/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 02:07:49 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/07 22:34:58 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_unset(t_shell *shell, t_cmd *cmd)
{
	if (cmd->args && cmd->args[1])
		unset_env(shell, cmd->args[1]);
}
