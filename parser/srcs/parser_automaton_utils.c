/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_automaton_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 10:55:31 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/16 14:36:58 by dthalman         ###   ########.fr       */
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

void	auto_load_size(int fd, t_automaton *au)
{
	char	*str;
	char	*line;

	line = read_ignore_comment(fd);
	str = line;
	au->cols = ft_atoi(str);
	while (*str && is_space(*str))
		str++;
	while (*str && is_digit(*str))
		str++;
	au->rows = ft_atoi(str);
}

void	auto_load_indexes(int fd, t_automaton *au)
{
	int		c;
	int		idx;
	char	*str;

	str = read_ignore_comment(fd);
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
		str = read_ignore_comment(fd);
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

void	auto_load_accepting(int fd, t_automaton *au)
{
	int		v;
	int		idx;
	char	*str;

	idx = -1;
	str = read_ignore_comment(fd);
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

int	get_char_index(const int c, t_automaton *au)
{
	if (c < 0 || c > CHAR_INDEXES_LEN - 1 || !au->char_indexes)
		return (0);
	else
		return (au->char_indexes[c]);
}
