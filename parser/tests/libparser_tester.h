/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libparser_tester.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:15:55 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/16 13:38:37 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPARSER_TESTER_H
# define LIBPARSER_TESTER_H
# include "libparser.h"

int		main(int argc, char **argv);
void	test_automaton(void);
void	valid_automaton(char *str);
void	valid_automaton_str(char *wildcard, char *str);
int		token_tester(char *input);
void	test_print_transition(t_automaton *oto);
int		token_automaton_tester(char *input);
void	token_print(t_token *token);
#endif
