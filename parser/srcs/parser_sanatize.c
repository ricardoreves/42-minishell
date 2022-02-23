/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sanatize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 08:51:29 by dthalman          #+#    #+#             */
/*   Updated: 2022/02/23 10:17:46 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libparser.h"
#include "libft.h"
#include <stdlib.h>

/**
 * @brief supprime les guillements de la liste
 * 
 * @param token 
 */
void	sanatize_quotes_token(t_token *token)
{
	t_token	*t;
	int		i;
	int		decal;
	int		len;	

	t = token;
	while (t)
	{
		if (t->id == id_dbl_quotes || t->id == id_single_quotes)
		{
			len = ft_strlen(t->str);
			i = -1;
			while (++i < len - 2)
				t->str[i] = t->str[i + 1];
			t->str[i] = '\0';
		}
		if (t->id == id_word)
		{
			len = ft_strlen(t->str);
			i = -1;
			decal = 0;
			while (++i < len - decal)
			{
				if (t->str[i] == '\'' || t->str[i] == '"')
					decal++;
				t->str[i] = t->str[i + decal];
			}
			t->str[i] = '\0';
		}
		t = t->next;
	}
}

/**
 * @brief remplace les variables d'environnment et identifie si
 * c'est un executable 
 * 
 * @param token 
 * @param shell 
 */
void	exec_ident_token(t_token *token, t_shell *shell)
{
	t_token	*t;
	char	*str;
	int		last_id;

	t = token;
	last_id = id_notset;
	while (t)
	{
		if (t->id == id_word)
		{
			str = eval_varenv_str(shell, t->str, 0);
			free(t->str);
			t->str = str;
			is_token_builtin(t);
		}
		last_id = t->id;
		t = t->next;
	}
}

void	is_token_builtin(t_token *token)
{
    if (str_compare(token->str, "cd") == 0)
        token->id = id_builtin_cd;
    else if (str_compare(token->str, "echo") == 0)
        token->id = id_builtin_echo;
    else if (str_compare(token->str, "env") == 0)
        token->id = id_builtin_env;
    else if (str_compare(token->str, "exit") == 0)
        token->id = id_builtin_exit;
    else if (str_compare(token->str, "export") == 0)
        token->id = id_builtin_export;
    else if (str_compare(token->str, "pwd") == 0)
        token->id = id_builtin_pwd;
    else if (str_compare(token->str, "unset") == 0)
        token->id = id_builtin_unset;
}