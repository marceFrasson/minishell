/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_II.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:44:22 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/17 11:56:59 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	delete_local_variable(char *token)
{
	int	i;

	i = -1;
	while (g_global.local_variable[++i])
	{
		if (!ft_strcmp(g_global.local_variable[i], token))
		{
			while (g_global.local_variable[i + 1])
			{
				g_global.local_variable[i] = g_global.local_variable[i + 1];
				g_global.local_path[i] = g_global.local_path[i + 1];
				i++;
			}
			break ;
		}
	}
}

static void	delete_env_variable(char *token)
{
	int	i;

	i = -1;
	while (g_global.env_variable[++i])
	{
		if (!ft_strcmp(g_global.env_variable[i], token))
		{
			while (g_global.env_variable[i + 1])
			{
				g_global.env_variable[i] = g_global.env_variable[i + 1];
				g_global.env_path[i] = g_global.env_path[i + 1];
				i++;
			}
			break ;
		}
	}
}

void	delete_variable(char *token, int is_env)
{
	if (is_env)
		delete_env_variable(token);
	else
		delete_local_variable(token);
}
