/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 21:28:31 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/28 16:57:31 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void change_dir(t_shell *shell, char *path)
{
    if (chdir(path) != 0)
        put_command_error(shell, "cd", strerror(errno), errno);
}

void update_pwd(t_shell *shell, char *name)
{
    char cwd[256];

    ft_bzero(cwd, sizeof(cwd));
    if (getcwd(cwd, sizeof(cwd)))
    {
        //printf("UPDATE_PWD>>%s: %s\n", name, cwd);
        set_env(shell, ft_strdup(name), ft_strdup(cwd));
    }
    else
        perror("Error: getcwd() failed");
}

int exec_cd(t_shell *shell, char *args[])
{
    int i;
    char **dirs;

    // add_env(shell, ft_strdup("KKKK"), ft_strdup("0"));
    update_pwd(shell, "OLDPWD");

    //add_env(shell, ft_strdup("MAR"), ft_strdup("555"));
    //set_env(shell, ft_strdup("MAR"), ft_strdup("9999999"));
    //printf("EXEC_CD>>%s\n", get_env(shell, "MAR"));

    // print_array(shell->envs);

    //
    if (!args[1] || (args[1] && str_compare(args[1], "~") == 0))
        change_dir(shell, get_env(shell, "HOME"));
    else if (args[1] && str_compare(args[1], "-") == 0)
        ft_putendl_fd(get_env(shell, "PWD"), 1);
    else if (ft_strchr(args[1], '/') != 0)
    {
        i = -1;
        dirs = ft_split(args[1], '/');
        while (dirs[++i])
            change_dir(shell, dirs[i]);
    }
    else
        change_dir(shell, args[1]);
    update_pwd(shell, "PWD");
    //printf("EXEC_CD>>%s\n", get_env(shell, "OLDPWD"));
    //printf("EXEC_CD>>%s\n", get_env(shell, "PWD"));
    return (0);
}

// bash: cd: fff: No such file or directory
/*
cd (change to home)
cd .
cd ..
cd $HOME
cd fakepath
cd tmp/gnl
cd //
 */