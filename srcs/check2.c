/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 01:07:26 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/12 01:23:17 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief contrôle que les commandes sont correctement formaté
 * 
 * @param shell 
 * @return int 
 */
int	is_valid_commands(t_shell *shell)
{
	if (is_unexpected_token_command(shell))
		return (0);
	if (!is_valid_here_doc(shell))
		return (0);
	return (1);
}

int	is_invalid_command(t_shell *shell, t_cmd *cmd)
{
	if (is_directory(cmd->name))
		show_command_error(shell, cmd->name, MSG_IS_DIRECTORY, 126);
	else if (is_file_not_found(cmd->name))
		show_command_error(shell, cmd->name, MSG_FILE_NOT_FOUND, 127);
	else if (is_command_not_found(get_env(shell, "PATH"), &cmd->name, 0))
		show_command_error(shell, cmd->name, MSG_COMMAND_NOT_FOUND, 127);
	else if (is_file_permission_denied(cmd->name))
		show_command_error(shell, cmd->name, MSG_PERMISSION_DENIED, 126);
	return (shell->exit_status);
}

int	is_unexpected_token_command(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmds;
	while (cmd)
	{
		if (!cmd->name)
		{
			show_command_error(shell, NULL, MSG_SYNTAX_ERROR, 2);
			save_exit_status(shell);
			return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}

/**
 * @brief retourne 1 si il n'y a pas de heredoc ou que ceux-si
 * sont correctement configuré dans la commande
 * 
 * @param shell 
 * @return int 
 */
int	is_valid_here_doc(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmds;
	while (cmd)
	{
		if (cmd->redirect_id == id_in_std && !cmd->redirect_path)
		{
			show_command_error(shell, NULL, MSG_SYNTAX_ERROR, 2);
			save_exit_status(shell);
			return (0);
		}
		cmd = cmd->next;
	}
	return (1);
}

int	is_builtin_command( t_cmd *cmd)
{
	if (str_compare(cmd->name, "cd") == 0)
		return (1);
	else if (str_compare(cmd->name, "echo") == 0)
		return (1);
	else if (str_compare(cmd->name, "env") == 0)
		return (1);
	else if (str_compare(cmd->name, "exit") == 0)
		return (1);
	else if (str_compare(cmd->name, "export") == 0)
		return (1);
	else if (str_compare(cmd->name, "pwd") == 0)
		return (1);
	else if (str_compare(cmd->name, "unset") == 0)
		return (1);
	else
		return (0);
}
