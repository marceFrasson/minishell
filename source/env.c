/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:50:53 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/16 20:25:34 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_env(void)
{
	int	i;

	i = -1;
	while (g_global.env_variable[++i])
	{
		ft_putstr_fd(g_global.env_variable[i], STDOUT);
		ft_putstr_fd("=", STDOUT);
		ft_putendl_fd(g_global.env_path[i], STDOUT);
	}
	g_global.status = 0;
}
