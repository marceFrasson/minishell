/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_I.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:12:04 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/16 20:46:29 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_variables(void)
{
	int	i;

	i = -1;
	printf("\n--------\n");
	while (g_global.local_variable[++i])
		printf("%s=%s\n", g_global.local_variable[i], g_global.local_path[i]);
	printf("--------\n\n");
}

void	adding_variables(char **tokens)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (!check_for_operators_or_quotes(tokens))
	{
		while (tokens[++i])
		{
			while (tokens[i][++j])
			{
				if (tokens[i][j] == '=')
				{
					g_global.local_variable[g_global.count_local]
						= ft_substr(tokens[i], 0, j);
					g_global.local_path[g_global.count_local++]
						= ft_substr(tokens[i], j + 1, ft_strlen(tokens[i]) - 1);
					j = -1;
					break ;
				}
			}
		}
	}
	print_variables();
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
