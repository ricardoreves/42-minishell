/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libparser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 08:51:29 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/10 07:50:11 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPARSER_H
# define LIBPARSER_H
# define SPACE_SEPARATOR " \t\v\f\n" 
# define NON_CHAR_IDENTIFIER " ()<>|&;!><\t\v\f\n"
# include <stdio.h>
typedef enum e_expression_type
{
	expression,
	other
}	t_type;
typedef struct s_parse_tree
{
	t_type	type;
	int		line;
	int		pos;
}	t_parse_tree;
typedef struct s_token
{
	int				position;
	char			*str;
	struct s_token	*next;
}	t_token;
void			ft_move_space_forward(char const *s, int *pos);
void			ft_token_dispose(t_token **token);
void			ft_add_token(t_token **token, char *start, int len, int pos);
int				ft_is_redirection(int c);
int				ft_is_pipe(int c);
int				ft_is_and(int c);
int				ft_is_eoe(int c);
int				ft_is_space(int c);
t_token			*ft_parse_token(char *str);
t_parse_tree	*ft_parse_tree(char **str);
#endif
