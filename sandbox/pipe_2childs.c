/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_pipe_and_redirect.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:03 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/06 17:13:13 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
        int pipefd[2];
        int fd;
        int status;
        pid_t cpid;

        char *cmd1[] = {"/bin/ls", "-l", 0};
        char *cmd2[] = {"/bin/wc", "-l", 0};

        if (pipe(pipefd) == -1)
        {
                perror("Error: pipe() failed");
                exit(EXIT_FAILURE);
        }
        cpid = fork();
        if (cpid > 0) // parent
        {
                close(pipefd[1]);

                cpid = fork();
                if (cpid == 0) // child 2
                {
                        fd = open("data.txt", O_CREAT | O_WRONLY, S_IRWXU); // O_APPEND
                        dup2(pipefd[0], STDIN_FILENO);
                        close(pipefd[0]);
                        dup2(fd, STDOUT_FILENO);
                        execve(cmd2[0], cmd2, envp);
                        close(fd);
                }
                else // parent
                {
                        close(pipefd[0]);
                }
        }
        else if (cpid == 0) // child 1
        {
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
                execve(cmd1[0], cmd1, envp);
        }
        else
        {
                perror("Error: fork() failed");
        }
        wait(&status);
        wait(&status);
        return 0;
}