/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:33:21 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/08 03:06:10 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char **args)
{
    if (str_compare(args[0], "cd") == 0)
        return (1);
    else if (str_compare(args[0], "echo") == 0)
        return (1);
    else if (str_compare(args[0], "env") == 0)
        return (1);
    else if (str_compare(args[0], "exit") == 0)
        return (1);
    else if (str_compare(args[0], "export") == 0)
        return (1);
    else if (str_compare(args[0], "pwd") == 0)
        return (1);
    else if (str_compare(args[0], "unset") == 0)
        return (1);
    else
        return (0);
}

void exec_builtin(t_shell *shell, char **args)
{

    if (str_compare(args[0], "cd") == 0)
        exec_cd(shell, args);
    else if (str_compare(args[0], "echo") == 0)
        exec_echo(shell, args);
    else if (str_compare(args[0], "env") == 0)
        exec_env(shell);
    else if (str_compare(args[0], "exit") == 0)
        exec_exit(shell);
    else if (str_compare(args[0], "export") == 0)
        exec_export(shell, args);
    else if (str_compare(args[0], "pwd") == 0)
        exec_pwd(shell);
    else if (str_compare(args[0], "unset") == 0)
        exec_unset(shell, args);
}