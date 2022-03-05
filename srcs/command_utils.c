/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:21:21 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/05 21:31:34 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_directory(char *path)
{
	struct stat statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

int is_file_permission_denied(char *name)
{
	return (access(name, X_OK) == -1);
}

int is_file_not_found(char *name)
{
	return (ft_strncmp(name, "./", 2) == 0 && access(name, F_OK) == -1);
}

int is_command_not_found(char *path, char **name)
{
	int i;
	char *pathname;
	char **paths;

	i = 0;
	paths = ft_split(path, ':');
	if (!path || !paths)
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