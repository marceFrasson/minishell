/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:50:53 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/09 17:29:28 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_env(int print_declare_x, int fdout)
{
    int i;

    i = -1;
	while (g_global.env_variable[++i])
	{
        if (print_declare_x)
            ft_putstr_fd("declare -x ", fdout);
        ft_putstr_fd(g_global.env_variable[i], fdout);
        ft_putstr_fd("=", fdout);
        ft_putendl_fd(g_global.env_path[i], fdout);
	}
	g_global.status = 0;
}
