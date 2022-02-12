/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_multiple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:03 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/12 04:42:50 by rpinto-r         ###   ########.fr       */
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

void create_child(int i, char **cmd, char *envp[], int *pipefd, int num_pipes, int num_cmds)
{
        int fd;
        int status;
        pid_t cpid;
        int out;
        int in;
        // int pipefd[2];

        char cmds[4][3][10] = {{"/bin/ls\0", "-l\0", 0},
                               {"/bin/cat\0", "-e\0", 0},
                               {"/bin/grep\0", "pdf\0", 0},
                               {"/bin/wc\0", "-l\0", 0}};

        char *cmds1[] = {"/bin/ls\0", "-l\0", 0};
        char *cmds2[] = {"/bin/grep\0", "pdf\0", 0};
        char *cmds3[] = {"/bin/cat\0", "-e\0", 0};

        in = 0;
        out = 1;
        // pipe(pipefd);
        cpid = fork();
        if (cpid == -1)
        {
                perror("Error: fork() failed");
        }
        else if (cpid == 0) // child
        {
                // printf("child: %d %d %d %d %d\n", i, num_cmds, in, out, cpid);
                if (i == 0)
                {
                        printf("first: %s\n", cmds1[0]);
                        close(pipefd[in]);
                        dup2(pipefd[out], STDOUT_FILENO);
                        // execve(cmds[i][0], (char **)cmds[i], envp);
                        execve(cmds1[0], cmds1, envp);
                        close(pipefd[out]);
                        // exit(0);
                }
                else if (i == num_cmds - 1)
                {
                        printf("last: %s\n", cmds2[0]);
                        close(pipefd[out]);
                        dup2(pipefd[in], STDIN_FILENO);
                        execve(cmds3[0], cmds3, envp);
                        // execve(cmds[i][0], (char **)cmds[i], envp);
                        close(pipefd[in]);

                        // exit(0);
                }
                else
                {
                        printf("middle: %s\n", cmds3[0]);
                        dup2(pipefd[in], STDIN_FILENO);
                        dup2(pipefd[out], STDOUT_FILENO);
                        // execve(cmds[i][0], (char **)cmds[i], envp);
                        execve(cmds2[0], cmds2, envp);
                        // close(pipefd[in]);
                        // close(pipefd[out]);
                        //  exit(0);
                }
        }
        else
        {
                waitpid(-1, &status, 0);
                printf("parent process %d\n", i);
                close(pipefd[out]);
                // close(pipefd[out + 1]);
        }

        // close(pipefd[in]);
        // close(pipefd[out]);
        //  i = 0;
        //  while (i <= in)
        //  {
        //          close(pipefd[i]);
        //          i++;
        //  }
        //  else
        //  {
        //          // waitpid(-1, &status, 0);
        //          close(pipefd[1]);

        //         // dup2(pipefd[0], STDIN_FILENO);
        //         // // fd = open(redi1[1], O_RDONLY, S_IRWXU);
        //         // // dup2(fd, STDIN_FILENO);
        //         // // dup2(fd, STDIN_FILENO);

        //         // execve(cmd2[0], cmd2, envp);

        //         close(pipefd[0]);
        // }
}

int main(int argc, char *argv[], char *envp[])
{
        int i;
        int status;
        pid_t cpid;

        int *pipefd;
        int filefd[3];
        int num_cmds;
        int num_pipes;

        char cmds[4][3][10] = {{"/bin/ls\0", "-l\0", 0},
                               {"/bin/cat\0", "-e\0", 0},
                               {"/bin/grep\0", "pdf\0", 0},
                               {"/bin/wc\0", "-l\0", 0}};

        num_cmds = 3;
        // while (cmds[num_cmds])
        //          num_cmds++;

        num_pipes = 2 * num_cmds - 1; // two cmds 1 pipe, three cmds 2 pipes...
        printf("num_cmds: %d num_pipes: %d\n", num_cmds, num_pipes);
        pipefd = ft_calloc(sizeof(int), num_pipes);

        i = 0;
        while (i < num_cmds - 1)
        {
                printf("%d\n", 2 * i);
                if (pipe(pipefd + (2 * i)) == -1)
                {
                        perror("Error: pipe() failed");
                        exit(EXIT_FAILURE);
                }
                i++;
        }
        i = 0;
        while (i < num_cmds)
        {
                // printf("cmd: %d %s\n", i, cmds[i][0]);
                create_child(i, (char **)cmds[i], envp, pipefd, num_pipes, num_cmds);
                i++;
        }
        // waitpid(-1, &status, 0);
        return 0;
}