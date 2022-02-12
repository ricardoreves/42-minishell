/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 10:57:54 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/11 10:57:54 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFER_SIZE 256

typedef struct s_buffer_read
{
	int		fd;
	int		pos;
	int		pos_end;
	int		size;
	int		last_read;
	char	buffer[BUFFER_SIZE + 1];
} t_buffer_read;

int	slen(char *s)
{
	int	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

char	*join(char *s1, char *s2, int l2)
{
	int		len1;
	int 	len2;
	int		i;
	char	*ret;

	if (s1)
		len1 = slen(s1);
	else
		len1 = 0;
	if (s2)
		len2 = slen(s2);
	else
		len2 = 0;
	if (l2 < len2)
		len2 = l2;
	ret = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!ret)
		return (0);
	i = -1;
	while (++i < len1)
		ret[i] = s1[i];
	i--;
	while (++i < len1 + len2)
		ret[i] = s2[i - len1];
	ret[i] = 0;
	free(s1);
	return (ret);
}

char	*get_nextline(int fd)
{
	static t_buffer_read	buf;
	char					*ret;

	ret = 0;
	if (buf.pos == buf.last_read)
	{
		buf.last_read = read(fd, buf.buffer, BUFFER_SIZE);
		buf.buffer[buf.last_read] = 0;
		buf.pos = 0;
	}
	while (buf.last_read && buf.buffer[buf.pos] != '\n')
	{
		if (buf.pos >= buf.last_read)
		{
			buf.last_read = read(fd, buf.buffer, BUFFER_SIZE);
			buf.buffer[buf.last_read] = 0;
			buf.pos = 0;
		}
		buf.pos_end = buf.pos;
		while (buf.pos_end < buf.last_read && buf.buffer[buf.pos_end] != '\n')
			buf.pos_end++;
		ret = join(ret, (buf.buffer + buf.pos), (buf.pos_end) - buf.pos);
		buf.pos = buf.pos_end;
		if (buf.buffer[buf.pos_end] == '\n')
		{
			buf.pos++;			
			return (join(ret, "\n", 1));
		}
	}
	return (ret);
}