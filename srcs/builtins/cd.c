/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 21:28:31 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/05 01:32:54 by rpinto-r         ###   ########.fr       */
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
        set_env(shell, ft_strdup(name), ft_strdup(cwd));
    else
        perror("Error: getcwd() failed");
}

int exec_cd(t_shell *shell, t_cmd *cmd)
{
    int i;
    char **dirs;

    update_pwd(shell, "OLDPWD");
    if (!cmd->args[1] || (cmd->args[1] && (str_compare(cmd->args[1], "~") == 0 || str_compare(cmd->args[1], "~/") == 0)))
        change_dir(shell, get_env(shell, "HOME"));
    else if (cmd->args[1] && str_compare(cmd->args[1], "-") == 0)
        ft_putendl_fd(get_env(shell, "PWD"), 1);
    else if (ft_strchr(cmd->args[1], '/') != 0)
    {
        i = -1;
        dirs = ft_split(cmd->args[1], '/');
        while (dirs[++i])
            change_dir(shell, dirs[i]);
        free_array(dirs);
    }
    else
        change_dir(shell, cmd->args[1]);
    update_pwd(shell, "PWD");
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