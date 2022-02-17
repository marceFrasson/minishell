/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_II.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 20:01:42 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/17 15:02:02 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	delete_from_local_variable(int index)
{
	int	i;

	i = index - 1;
	while (g_global.local_variable[++i])
	{
		g_global.local_variable[i] = g_global.local_variable[i + 1];
		g_global.local_path[i] = g_global.local_path[i + 1];
	}
}

void	add_to_env_variable(int index)
{
	g_global.env_variable[g_global.count_env] = g_global.local_variable[index];
	g_global.env_path[g_global.count_env++] = g_global.local_path[index];
	delete_from_local_variable(index);
}

int	does_token_match_local_variable(char *token)
{
	int	i;

	i = -1;
	while (g_global.local_variable[++i])
	{
		if (!ft_strcmp(token, g_global.local_variable[i]))
			return (i);
	}
	return (-1);
}

int	validate_tokens(char **tokens)
{
	int	i;
	int	j;

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
