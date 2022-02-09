/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_and_adding_variables.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:12:04 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/09 15:53:22 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	adding_variables(char **tokens)
{
	int i;

	i = -1;
	if (!check_for_operators(tokens))
	{
		while (tokens[++i])
		{
			if (!ft_strchr(tokens[i], '='))
				add_variable(tokens[i]);
		}
	}
}

void	add_variable(char *token)
{
	int		i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '=')
		{
			g_global.local_variable[g_global.count_local] = ft_substr(token, 0, i);
			g_global.local_path[g_global.count_local] = ft_substr(token, i + 1, ft_strlen(token) - 1);
			break ;
		}
		i++;
	}
}

char	*expanding_variable(char *token)
{
	char	*variable;
	int		i;

	i = 0;
	variable = malloc(sizeof(char *) * ft_strlen(token));
	strcpy(variable, token);
	while (!ft_strcmp(variable, g_global.env_variable[i]))
		i++;
	printf("i: %i\n", i);
	return (g_global.env_path[i]);
}
