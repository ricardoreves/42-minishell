/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 22:45:05 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/05 01:12:06 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void create_pids(t_shell *shell)
{
	shell->pids = ft_calloc(sizeof(int), shell->num_cmds);
}

void wait_pids(t_shell *shell)
{
	int i;
	int status;

	i = 0;
	while (i < shell->num_cmds)
		waitpid(shell->pids[i++], &status, 0);
	free(shell->pids);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
}