/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 21:28:31 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/06 04:35:24 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_shell *shell, char *name)
{
	char	cwd[256];

	ft_bzero(cwd, sizeof(cwd));
	if (getcwd(cwd, sizeof(cwd)))
	{
		if (get_env(shell, name))
			set_env(shell, ft_strdup(name), ft_strdup(cwd));
		else
			add_env(shell, ft_strdup(name), ft_strdup(cwd));
	}
	else
		perror("Error: getcwd() failed");
}

static char	*fix_home_path(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	char	*home;

	home = get_env(shell, "HOME");
	if (!home)
		return (0);
	if (cmd->args[1])
	{
		if (ft_strncmp(cmd->args[1], "~/", 2) == 0)
			path = ft_strjoin(ft_strdup(home), cmd->args[1] + 2);
		else if (str_compare(cmd->args[1], "~") == 0)
			path = ft_strdup(home);
		else
			path = ft_strdup(cmd->args[1]);
	}
	else
		path = ft_strdup(home);
	return (path);
}

int	exec_cd(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	char	*oldpwd;
	char	*tmp;

	path = fix_home_path(shell, cmd);
	if (!path)
		return (0);
	else if (str_compare(path, "-") == 0)
	{
		oldpwd = get_env(shell, "OLDPWD");
		tmp = path;
		if (!oldpwd)
			path = ft_strdup(get_env(shell, "PWD"));
		else
			path = ft_strdup(oldpwd);
		free(tmp);
	}
	update_pwd(shell, "OLDPWD");
	if (chdir(path) != 0)
		show_command_error(shell, cmd->name, strerror(errno), errno);
	update_pwd(shell, "PWD");
	free(path);
	return (0);
}
