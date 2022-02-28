/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:18:01 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/28 17:28:27 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_shell(t_shell *shell)
{
	if (shell->cmds)
		free_cmds(shell->cmds);
	if (shell->envs)
		free_array(shell->envs);
	if (shell->config)
		free(shell->config);
}