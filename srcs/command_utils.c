/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:21:21 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/10 15:09:48 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_exec_file(char *name)
{
	return (ft_strncmp(name, "./", 2) == 0 || name[0] == '/');
}

int	is_directory(char *name)
{
	struct stat	statbuf;

	if (stat(name, &statbuf) != 0)
		return (0);
	return ((S_ISDIR(statbuf.st_mode) && ft_strchr(name, '/') != 0));
}

int	is_file_permission_denied(char *name)
{
	return (access(name, X_OK) == -1);
}

int	is_file_not_found(char *name)
{
	return (is_exec_file(name) && access(name, F_OK) == -1);
}

int	is_command_not_found(char *path, char **name, int i)
{
	char	*pathname;
	char	**paths;

	if (is_exec_file(*name) && access(*name, F_OK) != -1)
		return (0);
	if (!path)
		return (1);
	paths = ft_split(path, ':');
	if (!paths)
		return (1);
	while (paths[i])
	{
		pathname = str_joins(paths[i++], (*name), "/");
		if (access(pathname, F_OK) != -1)
		{
			free((*name));
			free_array(paths);
			(*name) = pathname;
			return (0);
		}
		free(pathname);
	}
	free_array(paths);
	return (1);
}
