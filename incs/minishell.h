/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:18 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/01 22:50:31 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define NAME "\e[1;33mminishell\e[0m:"
#define DOLLAR "\e[1;37m$ \e[0m"
#define READ_END 0
#define WRITE_END 1
#define CONFIGFILE ".config/parser/bash.conf"

//#include <libft.h>
//#include <libparser.h>
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
} t_bash_token_id;

typedef struct s_cmd
{
	char			*name;
	char			**args;
	char			*redirect_path;
	t_bash_token_id redirect_id;
	struct s_cmd 	*next;
} t_cmd;

typedef struct s_shell
{
	char	*cmdline;
	char	*config;
	t_cmd 	*cmds;
	int		**pipes;
	int		*pids;
	char	**envs;
	int		num_cmds;
	int		num_pipes;
	int		error;
} t_shell;

void print_array(char *arr[]);
void free_array(char *arr[]);
int array_length(char *arr[]);
char **clone_array(char *arr[]);
void push_array(char *str, char ***arr);

char *get_evaluate_value(t_shell *shell, char *str, int *i);
char *evaluate_str_env(t_shell *shell, char *str, int k);

void free_shell(t_shell *shell);
void free_pipes(int **pipes, int size);

void close_pipes(t_shell *shell);
int create_pipes(t_shell *shell);

int contain_env(char *str, char *name);
int add_env(t_shell *shell, char *name, char *value);
char *get_env(t_shell *shell, char *name);
int set_env(t_shell *shell, char *name, char *value);
int unset_env(t_shell *shell, char *name);
int init_envs(t_shell *shell, char *envp[]);

void handle_signals(int signum);
void override_signals(void);

char *str_joins(char *str1, char *str2, char *sep);
char *str_duplicate_nbytes(char *str, size_t n);
int str_compare(char *str1, char *str2);

int put_command_error(t_shell *shell, char *cmd, char *msg, int num);

int exec_cd(t_shell *shell, char **args);
int exec_echo(t_shell *shell, char **args);
int exec_env(t_shell *shell);
int exec_exit(t_shell *shell);
int exec_export(t_shell *shell, char **args);
int exec_pwd(t_shell *shell);
int exec_unset(t_shell *shell, char **args);

void init_prompt(t_shell *shell);
void init_asciiart(void);
int is_builtin_command(char *name);
void exec_builtin_command(t_shell *shell, t_cmd *cmd);
int exec_single_command(t_shell *shell);
int access_command(char *path, char **name);
void handle_commands(t_shell *shell);
void process_command(t_shell *shell, t_cmd *cmd, int num);
void wait_pids(t_shell *shell);
void create_pids(t_shell *shell);
int is_directory_command(char *path);

int redirect_input(t_cmd *cmd);
int redirect_output(t_cmd *cmd);
void handle_redirect(t_cmd *cmd);

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

t_cmd *parse_command_line(t_shell *shell);
void sanitize_quotes_token(t_token *token);
void exec_ident_token(t_token *token, t_shell *shell);
void set_token_builtin(t_token *token);
char **token_to_string(t_token *token_from, t_token *token_to);
int is_id_builtin(int id);
int is_redirect(int id);
int is_word(int id);
void prepare_cmds(t_token *token, t_cmd **cmds);
void print_cmds(t_cmd *cmds);
void free_cmds(t_cmd *cmds);
int count_cmds(t_cmd *cmds);
#endif