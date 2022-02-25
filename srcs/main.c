/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:03 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/25 16:58:20 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_config(t_shell *shell)
{
    shell->configpath = str_joinsep(getcwd(0, 0), CONFIGFILE, "/");
}

void init_asciiart(void)
{
    printf("        _       _     \e[0;33m_          _ _ \e[0m\n");
    printf("  /\\/\\ (_)_ __ (_)\e[1;33m___| |__   ___| | |\e[0m\n");
    printf(" /    \\| | '_ \\| \e[0;33m/ __| '_ \\ / _ \\ | |\e[0m\n");
    printf("/ /\\/\\ \\ | | | | \e[0;33m\\__ \\ | | |  __/ | |\e[0m\n");
    printf("\\/    \\/_|_| |_|_\e[0;33m|___/_| |_|\\___|_|_|\e[0m\n");
    printf("\e[0;37mEmbrace the power of the command line ✨\e[0m\n\n");
}

void init_prompt(t_shell *shell)
{
    char *prompt;

    while (1)
    {
        prompt = str_joinsep(NAME, DOLLAR, get_env(shell, "PWD"));
        shell->cmdline = readline(prompt);
        if (*shell->cmdline != 0)
        {
            // set_env(shell, ft_strdup("MARVIN"), ft_strdup("0"));
            add_history(shell->cmdline);
            exec_command(shell);
        }
        free(shell->cmdline);
        free(prompt);
    }
}

int main(int argc, char *argv[], char *envs[])
{
    t_shell *shell;

    (void)argc;
    (void)argv;
    shell = ft_calloc(sizeof(t_shell), 1);
    //ft_memset(shell, 0, sizeof(shell));
    init_asciiart();
    init_envs(shell, envs);

    // test env_utils
    set_env(shell, ft_strdup("PATH"), str_joinsep(getenv("PATH"), getenv("PWD"), ":"));

    add_env(shell, ft_strdup("OLDPWD"), ft_strdup("/"));
    add_env(shell, ft_strdup("MARVIN"), ft_strdup("21"));
    // printf("%s\n", get_env(shell, "MARVIN"));

    set_env(shell, ft_strdup("MARVIN"), ft_strdup("42"));
    // printf("%s\n", get_env(shell, "MARVIN"));

    // unset_env(shell, "MARVIN");
    // printf("%s\n", get_env(shell, "MARVIN"));
    // //print_array(shell.envs);

    // printf("%s\n", eval_variable(shell, "Hi $USERNAME, Welcome$FAKE to $HOME$FAKE!\0", 0));int g_num = 0;

    // override_signals();
    init_config(shell);
    init_prompt(shell);
    // free_array(shell.envs);
    return (0);
}
