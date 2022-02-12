/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_readline.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 10:57:54 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/12 17:26:37 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_READLINE_H
# define PARSER_READLINE_H
# define BUFFER_SIZE 2

typedef struct s_buffer_read
{
	int		fd;
	int		pos;
	int		pos_end;
	int		size;
	int		last_read;
	char	buffer[BUFFER_SIZE + 1];
}	t_buffer_read;
int		slen(char *s);
char	*join(char *s1, char *s2, int l2);
void	read_buffer(int fd, t_buffer_read *buf);
char	*get_nextline(int fd);
#endif