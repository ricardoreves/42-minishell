/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:18 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/26 15:14:26 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define NAME "\e[1;33mminishell\e[0m:"
#define DOLLAR "\e[1;37m$ \e[0m"
#define READ_END 0
#define WRITE_END 1
#define CONFIGFILE ".config/parser/bash.conf"

#include "../libft/libft.h"
#include "../parser/inc/libparser.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

typedef enum e_bash_token_id
{
	id_notset = -2,
	id_blank = -1,
	id_dbl_quotes = 1,
	id_single_quotes,
	id_out_write, // >
	id_out_append,// >>
	id_in_file,  // <
	id_in_std,  // <<
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
}	t_bash_token_id;

typedef struct s_shell
{
	char *cmdline;
	char **cmds;
	char **envs;
	char *configpath;
	int error;
} t_shell;

typedef enum e_redirect
{
	NO_REDIRECT,   // 0
	INPUT_SINGLE,  // <
	INPUT_DOUBLE,  // <<
	OUTPUT_SINGLE, // >
	OUTPUT_DOUBLE  // >>
} t_redirect;

typedef struct s_cmd
{
	char 			*name;
	char			 **args;
	int				redirect;
	char 			*filename;
	struct s_cmd	*next;
} t_cmd;

void print_array(char *arr[]);
void free_array(char *arr[]);
int array_length(char *arr[]);
char **clone_array(char *arr[]);
void	push_array(char *str, char ***arr);

char *get_varenv_value(t_shell *shell, char *str, int *i);
char *eval_varenv_str(t_shell *shell, char *str, int k);
char **eval_varenv_map(t_shell *shell, char *arr[]);

int contain_env(char *str, char *name);
int add_env(t_shell *shell, char *name, char *value);
char *get_env(t_shell *shell, char *name);
int set_env(t_shell *shell, char *name, char *value);
int unset_env(t_shell *shell, char *name);
int init_envs(t_shell *shell, char *envp[]);

void signal_handler(int signum);
void override_signals(void);

char *str_joinsep(char *str1, char *str2, char *sep);
char *str_duplicate_nbytes(char *str, size_t n);
int str_compare(char *str1, char *str2);
int put_command_error(t_shell *shell, char *cmd, char *msg);

int exec_cd(t_shell *shell, char **args);
int exec_echo(t_shell *shell, char **args);
int exec_env(t_shell *shell);
int exec_exit(t_shell *shell);
int exec_export(t_shell *shell, char **args);
int exec_pwd(t_shell *shell);
int exec_unset(t_shell *shell, char **args);

void init_prompt(t_shell *shell);
void init_asciiart(void);
int is_builtin(char **args);
void exec_builtin(t_shell *shell, char **args);
int exec_command(t_shell *shell);
char *get_command_path(t_shell *shell, char *name);

// Not used
typedef struct s_env
{
	char *name;
	char *value;
	struct s_env *next;
} t_env;

void free_envlst(t_env **envs);
void print_envlst(t_env **envs);
t_env *new_envlst(char *name, char *value);
t_env *get_envlst(t_env **envs, char *name);
int init_envslst(t_shell *shell, char *envs[]);
int add_envlst(t_env **envs, t_env *env);
int set_envlst(t_env **envs, char *name, char *value);
int unset_envlst(t_env **envs, char *name); // bug
char	**parse(t_shell *shell, char *config);
void	sanatize_quotes_token(t_token *token);
void	exec_ident_token(t_token *token, t_shell *shell);
void	set_token_builtin(t_token *token);
char	**token_to_string(t_token *token_from, t_token *token_to);
int		is_id_builtin(int id);
int 	is_redirect(int id);
int 	is_word(int id);
void	prepare_cmd(t_token *token, t_cmd **cmds);
void 	print_cmd(t_cmd *cmds);
void	free_cmd(t_cmd **cmds);
#endif