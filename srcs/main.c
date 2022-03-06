/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:03 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/06 15:07:04 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_asciiart(void)
{
    printf("        _       _     \e[0;33m_          _ _ \e[0m\n");
    printf("  /\\/\\ (_)_ __ (_)\e[1;33m___| |__   ___| | |\e[0m\n");
    printf(" /    \\| | '_ \\| \e[0;33m/ __| '_ \\ / _ \\ | |\e[0m\n");
    printf("/ /\\/\\ \\ | | | | \e[0;33m\\__ \\ | | |  __/ | |\e[0m\n");
    printf("\\/    \\/_|_| |_|_\e[0;33m|___/_| |_|\\___|_|_|\e[0m\n");
    printf("\e[0;37mEmbrace the power of the command line ✨\e[0m\n");
    printf("version %s\n\n", VERSION);
    log_message("start " VERSION);
}

void init_config(t_shell *shell)
{
    char cwd[256];

    ft_bzero(cwd, sizeof(cwd));
    if (getcwd(cwd, sizeof(cwd)))
        shell->config = str_joins(cwd, CONFIGFILE, "/");
}

void init_prompt(t_shell *shell)
{
    char *prompt;

    while (1)
    {
        prompt = get_env(shell, "PWD");
        if (!prompt)
            prompt = ft_strjoin(NAME, DOLLAR);
        else
            prompt = str_joins(NAME, DOLLAR, get_env(shell, "PWD"));
        shell->cmdline = readline(prompt);
        if (*shell->cmdline)
        {
            add_history(shell->cmdline);
            if (parse_command_line(shell))
            {
                log_cmds(shell->cmds);
                handle_commands(shell);
                free_cmds(shell->cmds);
            }
            else
                show_command_error(shell, "minishell", "syntax error near unexpected token", 2);
        }
        free(shell->cmdline);
        free(prompt);
    }
}

void *init_shell(t_shell *shell, int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    return (ft_memset(shell, 0, sizeof(t_shell)));
}

int main(int argc, char *argv[], char *envs[])
{
    t_shell shell;

    if (init_shell(&shell, argc, argv))
    {
        init_asciiart();
        init_signals();
        init_envs(&shell, envs);
        init_config(&shell);
        init_prompt(&shell);
    }
    return (0);
}
