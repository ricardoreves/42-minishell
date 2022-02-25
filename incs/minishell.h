/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:18 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/25 16:47:25 by rpinto-r         ###   ########.fr       */
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
	char **args;
	t_redirect redirect;
	char *filename;
} t_cmd;

void print_array(char *arr[]);
void free_array(char *arr[]);
int array_length(char *arr[]);
char **clone_array(char *arr[]);

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
void	is_token_builtin(t_token *token);
#endif