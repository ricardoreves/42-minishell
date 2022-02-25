/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libparser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 08:51:29 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/25 14:55:59 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPARSER_H
# define LIBPARSER_H
# define SPACE_SEPARATOR " \t\v\f\n" 
# define NON_CHAR_IDENTIFIER " ()<>|&;!><\t\v\f\n"
# define CHAR_INDEXES_LEN 256
# include <stdio.h>

enum e_bash_tokenid
{
	id_notset = -2,
	id_blank = -1,
	id_dbl_quotes = 1,
	id_single_quotes,
	id_out_write,
	id_out_append,
	id_in_file,
	id_in_std,
	id_pipe,
	id_start_parenthesis,
	id_end_parenthesis,
	id_and,
	id_or,
	id_word,
	id_exec,
	id_builtin_cd,
	id_builtin_echo,
	id_builtin_env,
	id_builtin_exit,
	id_builtin_export,
	id_builtin_pwd,
	id_builtin_unset
};

typedef struct s_parse_pos
{
	int		step;
	int		accepting;
	int		col;
	int		row;
	int		start_pos;
	int		end_pos;
	int		len;
	int		id;
	char	*str;
}	t_parse_pos;
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
	int				row;
	int				col;
	char			*str;
	int				id;
	struct s_token	*next;
}	t_token;
typedef struct s_automaton
{
	int		rows;
	int		cols;
	char	*char_indexes;
	int		*transitions;
	int		*accepting;
}	t_automaton;
void			token_dispose(t_token **token);
int				count_token(t_token *token);
void			add_token(t_token **token, t_parse_pos *ppos);
int				is_redirection(int c);
int				is_pipe(int c);
int				is_empy_line(char *str);
int				is_digit(int c);
int				is_space(int c);
char			*get_nextline(int fd);
t_automaton		*automaton_factory(char *filename);
void			automaton_dispose(t_automaton *au);
int				automaton_validator(t_automaton *au, char *str);
void			automaton_token(t_token **token, t_automaton *au, char *str);
#endif
