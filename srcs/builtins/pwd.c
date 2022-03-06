/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 02:07:43 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/06 04:33:26 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = get_env(shell, "PWD");
	if (pwd)
		ft_putendl_fd(pwd, 1);
	return (0);
}
