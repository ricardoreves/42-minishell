/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 00:26:04 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/01 00:26:34 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void close_pipes(t_shell *shell)
{
	int i;

	i = shell->num_pipes;
	while (i--)
	{
		if (close(shell->pipes[i][0]) != 0 || close(shell->pipes[i][1]) != 0)
			perror("Error: pipe close() failed");
	}
}

int create_pipes(t_shell *shell)
{
	int i;

	i = 0;
	shell->num_pipes = shell->num_cmds - 1;
	shell->pipes = (int **)ft_calloc(sizeof(int *), shell->num_pipes);
	if (!shell->pipes)
		return (0);
	i = 0;
	while (i < shell->num_pipes)
	{
		shell->pipes[i] = (int *)ft_calloc(sizeof(int), 2);
		if (pipe(shell->pipes[i]) != 0)
		{
			perror("Error: pipe() failed");
			return (0);
		}
		i++;
	}
	return (1);
}