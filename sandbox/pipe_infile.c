/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:03 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/10 03:12:18 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
        int pipefd[2];
        int fdin;
        int fdout;
        int fdout2;
        int status;
        pid_t cpid;
        char *filename = "sandbox/infile.txt";
        char buf[1];
        int ret;

        char *cmd1[] = {"/bin/echo", "Hello", 0};
        char *cmd2[] = {"/bin/cat", "-e", 0};

        fdin = open(filename, O_RDONLY, S_IRWXU);
        fdout = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        fdout2 = open(filename, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);

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
                // dup2(pipefd[1], STDOUT_FILENO); // STDOUT_FILENO = 1
                dup2(fdout, STDOUT_FILENO);
                execve(cmd1[0], cmd1, envp);
                close(pipefd[1]);
                close(fdout);
        }
        else // parent
        {
                wait(&status);
                close(pipefd[1]);

                // dup2(pipefd[0], STDIN_FILENO);
                dup2(fdin, STDIN_FILENO);
                execve(cmd2[0], cmd2, envp);

                close(pipefd[0]); // close parent pipin
                close(fdin);
        }
        return 0;
}
