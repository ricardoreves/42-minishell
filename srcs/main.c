/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:03 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/02 17:53:26 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//const char *pathname, char *const argv[], char *const envp[]
int execute_command(char *inpt)
{
    pid_t pid;
    int wstatus;
    char *const argv[] = {"/bin/ls", "-la", 0};
    char *const envp[] = {0};

    pid = fork();
    if (pid > 0)
    {
        wait(&wstatus);
        printf("Parent\n");
        if (strcmp(inpt, "exit") == 0)
        {
            //free(inpt);
            exit(0);
        }
    }
    else if (pid == 0)
    {

        if (inpt)
        {
            printf("Child\n");
            execve("/bin/ls", argv, envp);
        }
    }
    else
    {
        perror("Error: fork() failed\n");
    }
    return (0);
}

int check_access(const char *pathname)
{
    int fd = access(pathname, F_OK);
    if (fd == -1)
    {
        //perror("No such file or directory");
        printf("%s: %s: %s: %s\n", NAME, "cmd", pathname, strerror(errno));
        return (1);
    }
    return 0;
}

int main(int argc, char *argv[], char *envp[])
{
    //pid_t pid;
    //char *input;
    char cwd[256];
    t_minishell data;
    (void)argv;
     (void)argc;

    ft_memset(&data, 0, sizeof(data));
    int i;

    i = 0;
    while (envp[i])
       printf("%s\n", envp[i++]);

    char *path = getenv( "PATH" );
    envp = ft_split(path, ':');
    //while (envp[i])
    //    printf("%s\n", envp[i++]);

    while (42)
    {
        if (getcwd(cwd, sizeof(cwd)) == NULL)
            perror("getcwd() error");
        //printf("\033[0;32mminishell\033[0m:\033[0;36m%s\033[0m🐚 ", cwd);
        data.input = readline("minishell: ");
        printf("readline: |%s| getcwd: %s\n", data.input, cwd);
        //parse_command(argv);
        check_access("README_.md");
        execute_command(data.input);
    }

    return (0);
}