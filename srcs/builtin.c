/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:33:21 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/01 00:13:11 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin_command(char *name)
{
    if (str_compare(name, "cd") == 0)
        return (1);
    else if (str_compare(name, "echo") == 0)
        return (1);
    else if (str_compare(name, "env") == 0)
        return (1);
    else if (str_compare(name, "exit") == 0)
        return (1);
    else if (str_compare(name, "export") == 0)
        return (1);
    else if (str_compare(name, "pwd") == 0)
        return (1);
    else if (str_compare(name, "unset") == 0)
        return (1);
    else
        return (0);
}

void exec_builtin_command(t_shell *shell, t_cmd *cmd)
{
    if (str_compare(cmd->name, "cd") == 0)
        exec_cd(shell, cmd->args);
    else if (str_compare(cmd->name, "echo") == 0)
        exec_echo(shell, cmd->args);
    else if (str_compare(cmd->name, "env") == 0)
        exec_env(shell);
    else if (str_compare(cmd->name, "exit") == 0)
        exec_exit(shell);
    else if (str_compare(cmd->name, "export") == 0)
        exec_export(shell, cmd->args);
    else if (str_compare(cmd->name, "pwd") == 0)
        exec_pwd(shell);
    else if (str_compare(cmd->name, "unset") == 0)
        exec_unset(shell, cmd->args);
}