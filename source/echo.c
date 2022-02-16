/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:03:58 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/16 20:15:16 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    command_echo(char **tokens, int fdout)
{
    int new_line;
    int i;

    i = 0;
    new_line = ON;
    if (!tokens[1])
		ft_putendl_fd("\0", fdout);
    else
    {
        if (!ft_strcmp(tokens[1], "-n"))
        {
            new_line = OFF;
            i++;
        }
        while (tokens[++i])
        {
            ft_putstr_fd(tokens[i], fdout);
            if (tokens[i + 1])
                ft_putstr_fd(" ", fdout);
        }
        if (new_line == ON)
            ft_putendl_fd("\0", fdout);
    }
    g_global.status = 0;
}
