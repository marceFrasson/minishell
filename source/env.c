/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:50:53 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/03 12:14:25 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_env(int ind, int fdout)
{
    int i;

    i = -1;
	while (g_global.envp_variable[++i])
	{
        if (ind)
            ft_putstr_fd("declare -x ", fdout);
        ft_putstr_fd(g_global.envp_variable[i], fdout);
        ft_putstr_fd("=", fdout);
        ft_putendl_fd(g_global.envp_path[i], fdout);
	}
	g_shell.status = 0;
}

