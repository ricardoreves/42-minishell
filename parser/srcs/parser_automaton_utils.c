/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_automaton_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 10:55:31 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/12 18:00:38 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libparser.h"
#include "parser_automaton.h"
#include "libft.h"

void	read_ignore_comment(char **line, int fd)
{
	*line = get_nextline(fd);
	while (*line && (is_empy_line(*line) || **line == '#'))
	{
		free(*line);
		*line = get_nextline(fd);
	}
}

void	auto_load_size(int fd, t_automaton *au)
{
	char	*str;
	char	*line;

	read_ignore_comment(&line, fd);
	str = line;
	au->cols = ft_atoi(str);
	while (*str && is_space(*str))
		str++;
	while (*str && is_digit(*str))
		str++;
	au->rows = ft_atoi(str);
	free(line);
}

void	auto_load_indexes(char *str, t_automaton *au)
{
	int	c;
	int	idx;

	while (str && *str)
	{
		c = ft_atoi(str);
		while (*str && is_space(*str))
			str++;
		while (*str && is_digit(*str))
			str++;
		idx = ft_atoi(str);
		while (*str && is_space(*str))
			str++;
		while (*str && is_digit(*str))
			str++;
		while (*str && is_space(*str))
			str++;
		if (c < CHAR_INDEXES_LEN && idx < au->cols)
			au->char_indexes[c] = idx;
		if (!is_space(*str) && !is_digit(*str))
			break ;
	}
}

void	auto_load_transitions(int fd, t_automaton *au)
{
	int		row;
	int		col;
	char	*str;

	row = -1;
	while (++row < au->rows)
	{
		read_ignore_comment(&str, fd);
		if (!str || !*str)
			break ;
		col = -1;
		while (str && *str && ++col < au->cols)
		{
			au->transitions[col + (row * au->cols)] = ft_atoi(str);
			while (*str && is_space(*str))
				str++;
			while (*str && is_digit(*str))
				str++;
			while (*str && is_space(*str))
				str++;
			if (!is_space(*str) && !is_digit(*str))
				break ;
		}
	}
}

void	auto_load_accepting(char *str, t_automaton *au)
{
	int	v;
	int	idx;

	idx = -1;
	while (str && *str && ++idx < au->rows)
	{
		v = ft_atoi(str);
		while (*str && is_space(*str))
			str++;
		while (*str && is_digit(*str))
			str++;
		while (*str && is_space(*str))
			str++;
		au->accepting[idx] = v;
		if (!is_space(*str) && !is_digit(*str))
			break ;
	}
}
