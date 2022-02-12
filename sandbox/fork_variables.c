/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:03 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/12 09:56:13 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[], char *envp[])
{
	int cpid;
	int wstatus;
	char c = 'c';
	char *pc = 0;
	
	pc = malloc(1);
	*pc = 'c';

	cpid = fork();
	if (cpid == -1) // erreur
	{
		perror("Error: fork() failed");
		exit(EXIT_FAILURE);
	}
	else if (cpid == 0) // child 1
	{
		(*pc)++;
		printf("child : change [c] to [%c]\n", ++c);
		printf("child : change [pc] [%p]\n", pc);
		printf("child : change [pc] to [%c]\n", *pc);
	}
	else // parent
	{
//		sleep(1);
		(*pc)++;
		printf("parent : change [c] to [%c]\n", ++c);
		printf("parent : change [pc] [%p]\n", pc);
		printf("parent : change [pc] to [%c]\n", *pc);
	}
	if (cpid)
	{
		waitpid (cpid, &wstatus, 0);
		free (pc);
	}

	return (0);
}
