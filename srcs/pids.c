/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 22:45:05 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/04 18:55:30 by rpinto-r         ###   ########.fr       */
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

	i = 0;
	while (i < shell->num_cmds)
	{
		// printf("num: %d pid: %d\n", i, shell->pids[i]);
		waitpid(shell->pids[i], shell->exit_status, 0);
		i++;
	}
	free(shell->pids);
	if (WIFEXITED(shell->exit_status))
	{
		printf("terminé, code=%d\n", WEXITSTATUS(shell->exit_status));
	}
}