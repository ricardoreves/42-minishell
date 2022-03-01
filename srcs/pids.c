/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 22:45:05 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/01 23:28:31 by rpinto-r         ###   ########.fr       */
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
	int wstatus;

	i = 0;
	while (i < shell->num_cmds)
	{
		// printf("num: %d pid: %d\n", i, shell->pids[i]);
		waitpid(shell->pids[i], &wstatus, 0);
		i++;
	}
	free(shell->pids);
}