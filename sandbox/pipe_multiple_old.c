/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_multiple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:03 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/11 15:51:09 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* 
ls -l > output.txt | cat -e
ls -l | grep pdf | cat -e
 */

#include "../incs/minishell.h"

// void create_pipes(t_shell *shell)
// {
//         if (pipe(pipefd) == -1)
//         {
//                 perror("Error: pipe() failed");
//                 exit(EXIT_FAILURE);
//         }

// }

void close_pipes(void)
{
}

void create_child(int i, char **cmd, char *envp[], int *pipefd1)
{
        int fd;
        int status;
        pid_t cpid;
        int pipefd[2];

        char *cmd2[] = {"/bin/cat", "-e", 0};
        char *arg2[] = {0};

        char *cmd1[] = {"/bin/ls", "-l", 0};
        char *redi1[] = {">", "output.txt", 0};
        
        pipe(pipefd);
        cpid = fork();
        if (cpid == -1) // parent
        {
                perror("Error: fork() failed");
        }
        else if (cpid == 0) // child 1
        {
               // if (i == 0)
                //{
                        close(pipefd[0]);
               // }
                int out = dup(fd);
                if (strcmp(redi1[0], ">") == 0)
                {
                        fd = open(redi1[1], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
                        dup2(fd, STDOUT_FILENO);
                }
                else if (strcmp(redi1[0], ">>") == 0)
                {
                        fd = open(redi1[1], O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
                        dup2(fd, STDOUT_FILENO);
                }
                else if (strcmp(redi1[0], "<") == 0)
                {
                        fd = open(redi1[1], O_RDONLY, S_IRWXU);
                        dup2(fd, STDIN_FILENO);
                }
                //dup2(pipefd[1], STDOUT_FILENO);

                execve(cmd1[0], cmd1, envp);
                //dup2(pipefd[1], fd);

                close(pipefd[1]);
                close(fd);
        }
        else
        {
                waitpid(-1, &status, 0);
                close(pipefd[1]);

                dup2(pipefd[0], STDIN_FILENO);
                //fd = open(redi1[1], O_RDONLY, S_IRWXU);
                //dup2(fd, STDIN_FILENO);
                //dup2(fd, STDIN_FILENO);

                execve(cmd2[0], cmd2, envp);

                close(pipefd[0]);    
        }
}

int main(int argc, char *argv[], char *envp[])
{
        int *pipefd;
        int num_cmds;
        int num_pipes;
        int filefd[3];
        int status;
        int i;
        pid_t cpid;

        // char cmds[2][4] = {{"/bin/ls", "-l", ">", "output", 0},
        //                 {"/bin/wc", "-l", "<", "output", 0}};

        char *cmds[] = {"/bin/ls", "-l", ">", "output.txt", 0};

        num_cmds = 2;
        num_pipes = 2 * num_cmds - 1; // two cmds 1 pipe, three cmds 2 pipes...
        pipefd = ft_calloc(sizeof(int), num_pipes);

        i = 0;
        while (i < num_cmds - 1)
        {
           
                if (pipe(pipefd + (2 * i)) == -1)
                {
                        perror("Error: pipe() failed");
                        exit(EXIT_FAILURE);
                }
            
                //printf("%d\n", *(pipefd + (1 * i)));
                //printf("%d\n", *(pipefd + (2 * i)));
                //printf("%d\n", *(pipefd + (2 * i)));
                i++;
        }
        i = 0;
        create_child(i, cmds, envp, pipefd);
        // while (i < num_cmds-1)
        // {
        //         create_child(i, cmds, envp, pipefd);
        //         i++;
        // }

        //waitpid(-1, &status, 0);
        return 0;
}