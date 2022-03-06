/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_automaton.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 10:55:31 by dthalman          #+#    #+#             */
/*   Updated: 2022/03/06 09:05:00 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_AUTOMATON_H
# define PARSER_AUTOMATON_H
# include "libparser.h"
# include "libft.h"

char		*read_ignore_comment(int fd);
t_list		**get_list_line(void);
void		dispose_list_line(void);
void		auto_load_size(int fd, t_automaton *au);
void		auto_load_indexes(int fd, t_automaton *au);
void		auto_load_transitions(int fd, t_automaton *au);
void		auto_load_accepting(int fd, t_automaton *au);
void		init_parse_pos(t_parse_pos *ppos, char *str);
int			allocate_automaton(t_automaton	*au);
t_automaton	*automaton_factory(char *filename);
void		automaton_dispose(t_automaton *au);
int			automaton_validator(t_automaton *au, char *str);
int			get_char_index(const int c, t_automaton *au);

void	auto_load_str_size(char *str, t_automaton *au);
int		count_char_in_str(char *str);
void	auto_load_str_indexes(char *str, t_automaton *au);
void	auto_load_str_transitions(char *str, t_automaton *au);
void	auto_load_str_accepting(char *str, t_automaton *au);
#endif
