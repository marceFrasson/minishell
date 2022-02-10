/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 19:54:27 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/10 13:25:05 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void add_to_env_variable(int index)
{
    g_global.env_variable[g_global.count] = g_global.local_variable[index];
    g_global.env_path[g_global.count++] = g_global.local_path[index];
}

static int  does_token_match_local_variable(char *token)
{
    int i;

    i = -1;
    while (g_global.local_variable[++i])
    {
        if (!ft_strcmp(token, g_global.local_variable[i]))
            return (i);
    }
    return (-1);
}

static int validate_tokens(char** tokens)
{
    int i;
    int j;

    i = 0;
    j = -1;
    while (tokens[++i])
    {
        while (tokens[i][++j])
        {
            if (ft_isalpha(tokens[i][j]) || (j > 0 && ft_isdigit(tokens[i][j])))
                j++;
            else
            {
                ft_putstr_fd("Minishell: export: `", 2);
                ft_putstr_fd(tokens[i], 2);
                ft_putstr_fd("': ", 2);
                ft_putendl_fd(strerror(errno), 2);
                return (0);
            }
        }
    }
    return (1);
}

void    command_export(char **tokens)
{
    int i;
    int index;

    i = 0;
    index = -1;
    if (validate_tokens(tokens))
    {
        while (tokens[++i])
        {
            index = does_token_match_local_variable(tokens[i]);
            if (index != DONT_MATCH)
                add_to_env_variable(index);
        }
    }
}
