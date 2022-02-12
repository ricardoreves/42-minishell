/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_automaton.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 10:55:31 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/12 17:46:40 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_AUTOMATON_H
# define PARSER_AUTOMATON_H
# include "libparser.h"

void		read_ignore_comment(char **line, int fd);
void		auto_load_size(int fd, t_automaton *au);
void		auto_load_indexes(char *str, t_automaton *au);
void		auto_load_transitions(int fd, t_automaton *au);
void		auto_load_accepting(char *str, t_automaton *au);
int			allocate_automaton(t_automaton	*au);
t_automaton	*automaton_factory(char *filename);
void		automaton_dispose(t_automaton *au);
#endif
