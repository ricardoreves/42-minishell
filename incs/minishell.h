/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:18 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/06 18:17:36 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\e[1;33mminishell\e[0m:$ "
# define READ_END 0
# define WRITE_END 1

# include "../libft/libft.h"
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

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;
	   
typedef struct s_shell
{
	char	*cmdline;
	char	**cmds;
	char	**envs;
	t_env	*envslst;
}	t_shell;

void print_array(char *array[]);
void free_array(char *array[]);
int array_length(char *array[]);
char **clone_array(char *array[]);

int add_env(t_shell *shell, char *name, char *value);
char *get_env(t_shell *shell, char *name);
int set_env(t_shell *shell, char *name, char *value);
int unset_env(t_shell *shell, char *name);
int init_envs(t_shell *shell, char *envp[]);

void signal_handler(int signum);
void override_signals(void);

char *ft_strsjoin(char *str1, char *str2, char *sep);
char *ft_strndup(char *str, size_t n);
int ft_strcmp(char *s1, char *s2);

int	execute_cd(t_shell *shell, char **args);
int execute_echo(t_shell *shell, char **args);
int execute_env(t_shell *shell);
int	execute_exit(t_shell *shell);
int execute_export(t_shell *shell, char **args);
int execute_pwd(t_shell *shell);
int execute_unset(t_shell *shell, char **args);


void show_ascii_art(void);
char *get_bin_pathname(t_shell *shell, char *name);
int is_builtin(char **args);
void execute_builtin(t_shell *shell, char **args);
int execute_command(t_shell *shell);


// Not used
void free_envlst(t_env **envs);
void print_envlst(t_env **envs);
t_env *new_envlst(char *name, char *value);
t_env *get_envlst(t_env **envs, char *name);
int init_envslst(t_shell *shell, char *envs[]);
int	add_envlst(t_env **envs, t_env *env);
int	set_envlst(t_env **envs, char *name, char *value);
int	unset_envlst(t_env **envs, char *name); // bug
#endif