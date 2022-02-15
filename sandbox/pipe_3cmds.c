#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../incs/minishell.h"

/* command pipeline: cat input1 | tr a-z A-Z | tr \\ q */

int close_pipes(int **pipes, int num_pipes)
{
    while (num_pipes--)
    {
        close(pipes[num_pipes][0]);
        close(pipes[num_pipes][1]);
    }
    return (0);
}

int child_process(int idx, int **pipes, int num_pipes, char *cmd, int num_cmds)
{
    pid_t pid1;
    pid1 = fork();

    int pipin;
    int pipout;
    int status;

    char **args;
    args = ft_split(cmd, ',');
    // print_array(args);
    // char *args[] = {"ls", "-l", 0};

    if (pid1 < 0)
    {
        perror("Error: fork() failed");
        return 1;
    }

    if (pid1 == 0)
    {
        if (idx < num_cmds - 1)
        {
            dup2(pipes[idx][1], 1); // output
        }

        if (idx > 0)
        {
            dup2(pipes[idx - 1][0], 0); // output
        }

        close_pipes(pipes, num_pipes);
        execvp(args[0], args);
        perror("Error: execve() failed");
        return 1;
    }
    else
    {
        printf("pid %d = %d\n", idx, pid1);
    }
    return (0);
}

int main(void)
{
    int pipe1[2];
    int pipe2[2];
    int status;
    int num_cmds;
    int num_pipes;
    int **pipes;
    int *files;
    int i;

    // Commands
    char *cmd1[] = {"ls", "-l", 0};
    char *cmd2[] = {"grep", "pdf", 0};
    char *cmd3[] = {"cat", "-e", 0};

    // "sed,s/pdf/txt/"
    char *cmds[] = {"ls,-l", "grep,pdf", "cat,-e", "wc,-l", 0};
    num_cmds = 0;
    while (cmds[num_cmds])
        cmds[num_cmds++];

    printf("num_cmds: %d\n", num_cmds);

    // Pipes
    num_pipes = num_cmds - 1;
    pipes = ft_calloc(sizeof(int *), num_pipes);
    if (!pipes)
        return (1);
    i = 0;
    while (i < num_pipes)
    {
        pipes[i] = ft_calloc(sizeof(int), 2);
        if (pipe(pipes[i]) != 0)
        {
            perror("Error: pipe() failed");
            return 1;
        }
        i++;
    }

    i = 0;
    while (i < num_cmds)
    {
        child_process(i, pipes, num_pipes, cmds[i], num_cmds);
        i++;
    }

    close_pipes(pipes, num_pipes);
    waitpid(-1, &status, 0);
    // wait(&status);

    return (0);
}