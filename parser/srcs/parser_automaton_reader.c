/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_automaton_reader.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 10:55:31 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/16 08:23:48 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libparser.h"
#include "parser_automaton.h"
#include "libft.h"

char	*read_ignore_comment(int fd)
{
	char	*line;
	t_list	**list;

	list = get_list_line();
	line = get_nextline(fd);
	ft_lstadd_front(list, ft_lstnew(line));
	while (line && (is_empy_line(line) || *line == '#'))
	{
		line = get_nextline(fd);
		ft_lstadd_front(list, ft_lstnew(line));
	}
	return (line);
}

t_list	**get_list_line(void)
{
	static t_list	*list;

	return (&list);
}

void	dispose_list_line(void)
{
	t_list	**list;

	list = get_list_line();
	ft_lstclear(list, free);
}
