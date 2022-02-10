/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:03 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/10 03:00:00 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
        int pipefd[2];
        int fd;
        int status;
        pid_t cpid;
        char *filename = "sandbox/outfile.txt";
        char buf[1];
        int ret;

        char *cmd1[] = {"/bin/ls", "-l", 0};
        char *cmd2[] = {"/bin/wc", "-l", 0};

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
                dup2(pipefd[1], STDOUT_FILENO); // STDOUT_FILENO = 1
                execve(cmd1[0], cmd1, envp);
                close(pipefd[1]);
        }
        else // parent
        {
                wait(&status);
                close(pipefd[1]);
                
                //fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
                fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
                dup2(pipefd[0], STDIN_FILENO);
                dup2(fd, STDOUT_FILENO);
                execve(cmd2[0], cmd2, envp);

                // fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
                // while (ret = read(pipefd[0], buf, 1))
                // {
                //         write(fd, buf, 1);
                // }
                close(pipefd[0]); // close parent pipin
                close(fd);
        }
        return 0;
}
