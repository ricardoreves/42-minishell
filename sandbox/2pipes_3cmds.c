#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../incs/minishell.h"

/* command pipeline: cat input1 | tr a-z A-Z | tr \\ q */

int close_pipes(int pipe1[2], int pipe2[2])
{
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);
    return (0);
}

int child_process(int idx, int pipe1[2], int pipe2[2], char *cmd1)
{
    pid_t pid1;
    pid1 = fork();

    char **args;
    args = ft_split(cmd1, '@');

    if (pid1 < 0)
    {
        perror("fork 1 failed");
        return 1;
    }

    if (pid1 == 0)
    {
        /* Child 1 - ls */
        if (idx == 0)
        {
            dup2(pipe1[1], 1);
        }
        if (idx == 1)
        {
            dup2(pipe1[0], 0);
            dup2(pipe2[1], 1);
        }
        if (idx == 2)
        {
            dup2(pipe2[0], 0);
        }
        close_pipes(pipe1, pipe2);
        execvp(args[0], args);
        perror("failed to execute cmd1");
        return 1;
    }
    printf("pid %d = %d\n", idx, pid1);
    return (0);
}

int main(void)
{
    int pipe1[2];
    int pipe2[2];
    int status;

    char *cmd1[] = {"ls", "-l", 0};
    char *cmd2[] = {"grep", "pdf", 0};
    char *cmd3[] = {"cat", "-e", 0};

    char *cmds[] = {"ls@-l\0", "cat@-e\0", "grep@pdf\0", 0};

    //char *cmds = {{"/bin/ls_-l\0"},
    //               {"/bin/cat_-e\0"},
    //               {"/bin/grep_pdf\0"}};

    if (pipe(pipe1) != 0 || pipe(pipe2) != 0)
    {
        perror("pipe failed");
        return 1;
    }

    int i = 0;
    int num_cmds = 3;
    while (i < num_cmds)
    {
        child_process(i, pipe1, pipe2, cmds[i]);
        i++;
    }

    close_pipes(pipe1, pipe2);
    waitpid(-1, &status, 0);

    return (0);
}