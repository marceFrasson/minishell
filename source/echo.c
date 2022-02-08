/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:03:58 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/07 22:28:43 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    command_echo(char **args, int fdout)
{
    int new_line;
    int i;

    i = 0;
    new_line = ON;
    if (!args[1])
		ft_putendl_fd("\0", fdout);
    else
    {
        if (!ft_strcmp(args[1], "-n"))
        {
            new_line = OFF;
            i++;
        }
        while (args[++i])
        {
            ft_putstr_fd(args[i], fdout);
            if (args[i + 1])
                ft_putstr_fd(" ", fdout);
        }
        if (new_line == ON)
            ft_putendl_fd("\0", fdout);
    }
    g_global.status = 0;
}
