/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libparser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 08:51:29 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/04 17:26:23 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPARSER_H
# define LIBPARSER_H
# define SEPARATOR " \t\v\f!><|;&()" 
# define SEPARATOR_COUNTED "!><|;&()"
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
int				ft_token_count(char const *str, char *sep, char *sepcmpt);
void			ft_move_forward(char const **s, char *sep, int not);
void			ft_pos_memcpy(char const *start, char const *end, char *mem);
int				ft_is_redirection(int c);
int				ft_is_pipe(int c);
int				ft_is_and(int c);
int				ft_is_eoe(int c);
char			**ft_parse_token(char *str);
t_parse_tree	*ft_parse_tree(char **str);
#endif
