/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 08:51:29 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/04 17:18:57 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libparser.h"
#include "libft.h"
#include <stdlib.h>

void	ft_move_space_forward(char const *s, int *pos)
{
	while (s[*pos] && ft_strchr(SPACE_SEPARATOR, s[*pos]))
		(*pos)++;
}

void	ft_add_token(t_token **token, char *start, int len, int pos)
{
	t_token	*t;
	t_token	*t2;
	int		i;
printf("[%d]\n",len);
if(len == 0) exit(0);

	t = malloc(sizeof(t_token));
	if (!t)
		return ;
	t->next = 0;
	t->position = pos;
	t->str = malloc((len) + 1);
	if(!t->str)
		return ;
	i = -1;
	while (++i < len)
		t->str[i] = start[i];
	t->str[i] = 0;
	if (!(*token))
		*token = t;
	else
	{
		t2 = (*token);
		while (t2->next)
			t2 = t2->next;
		t2->next = t;
	}
}

void	ft_token_dispose(t_token **token)
{
	t_token	*t;
	t_token	*p;

	t = *token;
	while (t)
	{
		p = t;
		t = t->next;
		free(p->str);
		free(p);
	}
	*token = 0;
}

t_token	*ft_parse_token(char *str)
{
	char 	*current;
	t_token	*token;
	int		pos;
	int		start_pos;
	int		final;

	token = 0;
	pos = 0;
	if (!str || !*str)
		return (0);
	current = str;
	while (current[pos])
	{

		ft_move_space_forward(current, &pos);
printf("[%c][%d]\n",current[pos], current[pos]);
		start_pos = pos;
		if (current[pos] && current[pos] == '"')
		{
			final = 0;
			while (current[pos] && !final)
			{
				pos++;
				if (current[pos] == '\\')
				{
					pos++;
					if (current[pos] == '"')
						pos++;
				} 
				else if (current[pos] == '"')
					final = 1;
			}
			if (final)
			{
				ft_add_token(&token, (current + start_pos), pos - start_pos + 1, pos);
				pos++;
			}
		}
		else if (current[pos] && current[pos] == '<')
		{
			if (current[pos + 1] == '<')
				pos++;
			ft_add_token(&token, (current + start_pos), (pos - start_pos) + 1, pos);
			pos++;
		}
		else if (current[pos] && current[pos] == '>')
		{
			if (current[pos + 1] == '>')
				pos++;
			ft_add_token(&token, (current + start_pos), (pos - start_pos) + 1, pos);
			pos++;
		}
		else if (current[pos] && current[pos] == '|')
		{
			ft_add_token(&token, (current + start_pos), 1, pos);
			pos++;
		}
		else if (current[pos] && current[pos] == ';')
		{
			ft_add_token(&token, (current + start_pos), 1, pos);
			pos++;
		}
		else if (current[pos] && current[pos] == '&')
		{
			if (current[pos + 1] == '&')
				pos++;
			ft_add_token(&token, (current + start_pos), (pos - start_pos) + 1, pos);
			pos++;
		}
		else if(current[pos])
		{
			final = 0;
			while (current[pos] && !final)
			{
				if (!ft_strchr(NON_CHAR_IDENTIFIER, current[pos]))
					pos++;
				else
					final = 1;
			}
			ft_add_token(&token, (current + start_pos), pos - start_pos, pos);
		}
	}
	return (token);
}
