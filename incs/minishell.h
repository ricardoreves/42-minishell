/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:18 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/12 01:23:17 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define VERSION "0.1.3"
# define NAME "\e[1;33mminishell\e[0m:"
# define DOLLAR "\e[1;37m$ \e[0m"
# define CONFIGFILE ".config/parser/bash.conf"
# define LOGFILE "minishell.log"
# define MSG_SYNTAX_ERROR "syntax error near unexpected token"
# define MSG_IS_DIRECTORY "is a directory"
# define MSG_FILE_NOT_FOUND "not such file or directory"
# define MSG_COMMAND_NOT_FOUND "command not found"
# define MSG_PERMISSION_DENIED "permission denied"

# include "libft.h"
# include "libparser.h"
# include "ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>

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
}	t_bash_token_id;

typedef struct s_cmd
{
	char			*name;
	char			**args;
	char			*redirect_path;
	t_bash_token_id	redirect_id;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	t_cmd	*cmds;
	char	*cmdline;
	char	*config;
	char	*working_dir;
	char	**envs;
	int		**pipes;
	int		*pids;
	int		num_cmds;
	int		num_pipes;
	int		exit_status;
	int		stop;
}	t_shell;

/* init */
void	init_asciiart(void);
void	init_config(t_shell *shell);
void	*init_shell(t_shell *shell, int argc, char *argv[]);
t_shell	*get_shell(void);
void	free_shell(t_shell *shell);

/* prompt */
char	*get_prompt_name(t_shell *shell);
void	init_prompt(t_shell *shell);

/* exec */
void	exec_commands(t_shell *shell);
int		exec_single_command(t_shell *shell, t_cmd *cmd);
void	exec_child_command(t_shell *shell, t_cmd *cmd, int num);
void	exec_builtin_command(t_shell *shell, t_cmd *cmd);

/* builtins */
void	exec_cd(t_shell *shell, t_cmd *cmd);
void	exec_echo(t_shell *shell, t_cmd *cmd);
void	exec_env(t_shell *shell);
void	exec_exit(t_shell *shell);
void	save_exit_status(t_shell *shell);
void	exec_export(t_shell *shell, t_cmd *cmd);
void	exec_pwd(t_shell *shell);
void	exec_unset(t_shell *shell, t_cmd *cmd);

/* check.c */
int		is_exec_file(char *name);
int		is_command_not_found(char *path, char **name, int i);
int		is_directory(char *name);
int		is_file_permission_denied(char *name);
int		is_file_not_found(char *name);
int		is_valid_commands(t_shell *shell);
int		is_invalid_command(t_shell *shell, t_cmd *cmd);
int		is_unexpected_token_command(t_shell *shell);
int		is_valid_here_doc(t_shell *shell);
int		is_builtin_command(t_cmd *cmd);

/* error */
int		show_command_error(t_shell *shell, char *cmd, char *msg, int num);

/* parsing */
int		parse_command_line(t_shell *shell);
void	evaluate_quotes_token(t_shell *shell, t_token *token);
void	sanitize_quotes_token(t_shell *shell, t_token *tokens);

/* parsing_utils */
void	set_builtin_token_id(t_token *token);
int		is_word_token_id(int id);
int		is_redirect_token_id(int id);
int		is_builtin_token_id(int id);

/* parsing_wildcard */
void	wildcard_cmds(t_shell *shell);
int		has_wildcard(char *str);
char	**get_wildcard_files(char *wildcard, t_shell *shell);

/* pids */
void	create_pids(t_shell *shell);
void	wait_pids(t_shell *shell);

/* pipes */
void	close_pipes(t_shell *shell);
int		create_pipes(t_shell *shell);
void	free_pipes(int **pipes, int size);

/* signals */
void	handle_echoctl(void);
void	handle_signals(int signum);
void	handle_signals_redisplay(int signum);
void	init_signals(int redisplay);

/* redirect */
void	handle_redirect_file(t_shell *shell, t_cmd *cmd);
void	redirect_input_file(t_shell *shell, t_cmd *cmd);
void	redirect_output_file(t_cmd *cmd);
void	redirect_input(t_shell *shell, t_cmd *cmd, int num);
void	redirect_output(t_shell *shell, t_cmd *cmd, int num);

/* heredoc */
void	here_doc(t_shell *shell, t_cmd *cmd, char *eof);
char	*get_tempfilename(t_shell *shell);
char	*here_doc_readline(void);
void	prepare_here_doc_cmd(t_shell *shell);

/* utils */
char	*str_joins(char *str1, char *str2, char *sep);
char	*str_duplicate_nbytes(char *str1, size_t n);
int		str_compare(char *str1, char *str2);

/* array_utils */
void	print_array(char *arr[]);
void	free_array(char *arr[]);
int		array_length(char *arr[]);
char	**clone_array(char *arr[]);
void	push_array(char *str, char ***arr);
void	remove_str_array(char *to_remove, char ***arr);
void	insert_array(char **new_arr, char *after, char ***arr);

/* cmd_utils */
void	push_cmd(t_cmd *cmd, t_cmd **cmds);
t_cmd	*create_cmd(t_shell *shell);
void	prepare_cmds(t_token *token, t_shell *shell);
void	free_cmds(t_cmd **cmds);

/* env_utils */
int		add_env(t_shell *shell, char *name, char *value);
char	*get_env(t_shell *shell, char *name);
int		set_env(t_shell *shell, char *name, char *value);
int		unset_env(t_shell *shell, char *name);
int		init_envs(t_shell *shell, char *envs[]);
int		contain_env(char *str, char *name);
char	*get_evaluate_value(t_shell *shell, char *str, int *i);
char	*evaluate_str_env(t_shell *shell, char *str, int k);

/* log */
int		ft_gettime(void);
int		log_open(void);
void	log_message(char *msg);
void	log_token(t_token *token);
void	log_cmds(t_cmd *cmds);
#endif