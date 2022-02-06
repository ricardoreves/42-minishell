/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:03 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/06 18:17:36 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void show_ascii_art(void)
{
    printf("        _       _     \e[1;33m_          _ _ \e[0m\n");
    printf("  /\\/\\ (_)_ __ (_)\e[1;33m___| |__   ___| | |\e[0m\n");
    printf(" /    \\| | '_ \\| \e[1;33m/ __| '_ \\ / _ \\ | |\e[0m\n");
    printf("/ /\\/\\ \\ | | | | \e[1;33m\\__ \\ | | |  __/ | |\e[0m\n");
    printf("\\/    \\/_|_| |_|_\e[1;33m|___/_| |_|\\___|_|_|\e[0m\n");
    printf("\e[1;37mEmbrace the power of the command line ✨\e[0m\n\n");
}

char *get_bin_pathname(t_shell *shell, char *name)
{
    int i;
    char *path;
    char *pathname;
    char **paths;

    i = 0;
    path = get_env(shell, "PATH");
    if (!path)
        return (0);
    paths = ft_split(path, ':');
    if (!paths)
        return (0);
    while (paths[i])
    {
        pathname = ft_strsjoin(paths[i++], name, "/");
        if (access(pathname, F_OK) != -1)
            return (pathname);
        free(pathname);
    }
    free_array(paths);
    return (0);
}

int is_builtin(char **args)
{
    if (ft_strcmp(args[0], "cd") == 0)
        return (1);
    else if (ft_strcmp(args[0], "echo") == 0)
        return (1);
    else if (ft_strcmp(args[0], "env") == 0)
        return (1);
    else if (ft_strcmp(args[0], "exit") == 0)
        return (1);
    else if (ft_strcmp(args[0], "export") == 0)
        return (1);
    else if (ft_strcmp(args[0], "pwd") == 0)
        return (1);
    else if (ft_strcmp(args[0], "unset") == 0)
        return (1);
    else
        return (0);
}

void execute_builtin(t_shell *shell, char **args)
{
    if (ft_strcmp(args[0], "cd") == 0)
        execute_cd(shell, args);
    else if (ft_strcmp(args[0], "echo") == 0)
        execute_echo(shell, args);
    else if (ft_strcmp(args[0], "env") == 0)
        execute_env(shell);
    else if (ft_strcmp(args[0], "exit") == 0)
        execute_exit(shell);
    else if (ft_strcmp(args[0], "export") == 0)
        execute_export(shell, args);
    else if (ft_strcmp(args[0], "pwd") == 0)
        execute_pwd(shell);
    else if (ft_strcmp(args[0], "unset") == 0)
        execute_unset(shell, args);
}

int execute_command(t_shell *shell)
{
    pid_t cpid;
    int status;
    char **args;
    char *pathname;

    cpid = fork();
    if (cpid == 0)
    {
        args = ft_split(shell->cmdline, ' ');
        printf("Child\n");
        if (is_builtin(args))
            execute_builtin(shell, args);
        else
        {
            pathname = get_bin_pathname(shell, args[0]);
            if (!pathname)
                printf("%s: command not found\n", args[0]);
            else if (execve(pathname, args, shell->envs))
                perror("Error: execve() failed");
            exit(0);
        }
        free_array(args);
    }
    if (cpid > 0)
    {
        // wait(&status);
        waitpid(cpid, &status, 0);
        printf("Parent\n");
        if (ft_strncmp(shell->cmdline, "exit", 4) == 0)
        {
            free_array(shell->envs);
            exit(0);
        }
    }
    if (cpid < 0)
    {
        perror("Error: fork() failed\n");
    }
    return (0);
}

int main(int argc, char *argv[], char *envs[])
{
    (void)argc;
    (void)argv;
    t_shell shell;

    show_ascii_art();
    ft_memset(&shell, 0, sizeof(shell));
    override_signals();

    init_envs(&shell, envs);
    set_env(&shell, ft_strdup("PATH"), ft_strsjoin(getenv("PATH"), getenv("PWD"), ":"));
    //printf("%s\n", get_env(&shell, "MARVIN"));
    //set_env(&shell, "MARVIN", "21");
    //printf("%s\n", get_env(&shell, "MARVIN"));
    // unset_env(&shell, "PATH");
    // free_array(shell.envs);

    // init_envslst(&shell, envs);
    // unset_envlst(&shell.envslst, "HOME");
    // print_envlst(&shell.envslst);
    // free_envlst(&shell.envslst);
    // add_envlst(&shell, "MARVIN", "42");
    // printf("%s\n", get_envlst(&shell, "MARVIN"));
    // set_envlst(&shell, "MARVIN", "21");
    // printf("%s\n", get_envlst(&shell, "MARVIN"));

    while (1)
    {
        shell.cmdline = readline(PROMPT);
        if (*shell.cmdline != 0)
        {
            add_history(shell.cmdline);
            execute_command(&shell);
        }
        free(shell.cmdline);
    }
    return (0);
}
