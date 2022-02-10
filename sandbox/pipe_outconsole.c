/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cout.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:03 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/08 20:27:02 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
        int pipefd[2];
        int status;
        pid_t cpid;

        if (pipe(pipefd) == -1)
        {
                perror("Error: pipe() failed");
                exit(EXIT_FAILURE);
        }
        cpid = fork();
        if (cpid == -1)
        {
                perror("Error: fork() failed");
                exit(EXIT_FAILURE);
        }
        else if (cpid == 0) // child 1
        {
                close(pipefd[0]); // close parent pipin
                write(pipefd[1], argv[0], strlen(argv[0]));
                close(pipefd[1]);
        }
        else // parent
        {
                char buf[1024];
                bzero(buf, 1024);
                wait(&status);
                close(pipefd[1]); // close parent pipout
                read(pipefd[0], buf, 1024);
                printf("%s", buf);
                close(pipefd[0]); // close parent pipin
        }
        return 0;
}