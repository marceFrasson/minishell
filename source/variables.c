/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:12:04 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/07 22:25:23 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_variable(char *token)
{
	int		i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '=')
		{
			g_global.variable[g_global.count] = ft_substr(token, 0, i);
			g_global.path[g_global.count] = ft_substr(token, i + 1, ft_strlen(token) - 1);
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
	while (!ft_strcmp(variable, g_global.variable[i]))
		i++;
	printf("i: %i\n", i);
	return (g_global.path[i]);
}
