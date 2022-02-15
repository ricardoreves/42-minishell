#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../incs/minishell.h"

int close_pipes(int **pipes, int num_pipes)
{
    while (num_pipes--)
    {
        close(pipes[num_pipes][0]);
        close(pipes[num_pipes][1]);
    }
    return (0);
}

int redirect_input(char *filename, char *redirect)
{
    int fd;

    if (strcmp(redirect, "<") == 0)
        fd = open(filename, O_RDONLY, S_IRWXU);
    if (strcmp(redirect, "<<") == 0)
        fd = open(filename, O_RDONLY, S_IRWXU);
    if (fd)
    {
        dup2(fd, 0);
        close(fd);
    }
    return (0);
}

int redirect_output(char *filename, char *redirect)
{
    int fd;

    if (strcmp(redirect, ">") == 0)
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    if (strcmp(redirect, ">>") == 0)
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
    if (fd)
    {
        dup2(fd, 1);
        close(fd);
    }
    return (0);
}

int child_process(int idx, int **pipes, int num_pipes, char **args, int num_cmds, char **redis)
{
    int status;
    pid_t pid;
    int fd;

    pid = fork();
    if (pid < 0) // Error
    {
        perror("Error: fork() failed");
        return 1;
    }
    else if (pid == 0) // Child
    {
        // input
        if (idx > 0)
        {
            dup2(pipes[idx - 1][0], 0);
        }
        else if (idx == 0) // first
        {
            redirect_input(redis[1], redis[0]);
        }

        // output
        if (idx < num_cmds - 1)
        {
            dup2(pipes[idx][1], 1);
        }
        else if (idx == num_cmds - 1) // last
        {
            redirect_output(redis[1], redis[0]);
        }
        close_pipes(pipes, num_pipes);
        // printf("|||%s\n", args[0]);
        execvp(args[0], args);
        perror("Error: execve() failed");
        return 1;
    }
    else // Parent
    {
        printf("pid %d = %d\n", idx, pid);
    }
    return (0);
}

int main(void)
{
    int i;
    int status;
    int num_cmds;
    int num_pipes;
    int **pipes;

    // Commands
    char *cmd1[] = {"ls", "-l", 0};
    char *cmd2[] = {"grep", "pdf", 0};
    char *cmd3[] = {"cat", "-e", 0};

    // char *cmds[][50] = {{"ls", "-l", 0},
    //                     {"grep", "pdf", 0},
    //                     {"cat", "-e", 0},
    //                     {"sed", "s/en.subject.pdf/fr.subject.txt/", 0},
    //                     {"tr", "a-z", "A-Z", 0}};

    char *redis[][50] = {{"<", "sandbox/infile.txt", 0},
                         {"42", "42", 0},
                         {">>", "sandbox/output.txt", 0},
                         {0}};

    char *cmds[][50] = {{"cat", 0},
                        {"grep", "Hello", 0},
                        {"cat", "-e", 0},
                        {0}};

    // Number of commands
    num_cmds = 0;
    while (cmds[num_cmds][0])
        num_cmds++;

    printf("num_cmds: %d\n", num_cmds);

    // Pipes
    num_pipes = num_cmds - 1;
    pipes = (int **)ft_calloc(sizeof(int *), num_pipes);
    if (!pipes)
        return (1);
    i = 0;
    while (i < num_pipes)
    {
        pipes[i] = (int *)ft_calloc(sizeof(int), 2);
        if (pipe(pipes[i]) != 0)
        {
            perror("Error: pipe() failed");
            return (1);
        }
        i++;
    }

    // Create child process
    i = 0;
    while (i < num_cmds)
    {
        child_process(i, pipes, num_pipes, (char **)cmds[i], num_cmds, redis[i]);
        i++;
    }
    close_pipes(pipes, num_pipes);
    waitpid(-1, &status, WCONTINUED);
    return (0);
}