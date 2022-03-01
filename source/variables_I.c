/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_I.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:12:04 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/17 15:15:15 by mfrasson         ###   ########.fr       */
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

int	does_token_match_env_variable(char *token)
{
	int	i;

	i = -1;
	while (g_global.env_variable[++i])
	{
		if (!ft_strcmp(token, g_global.env_variable[i]))
			return (i);
	}
	return (-1);
}

int	does_token_match_variable(char *token, char *temp_path)
{
	if (does_token_match_env_variable(token)
		!= DONT_MATCH)
	{
		g_global.env_path[g_global.count_env++] = temp_path;
		return (1);
	}
	if (does_token_match_local_variable(token)
		!= DONT_MATCH)
	{
		g_global.local_path[g_global.count_local++] = temp_path;
		return (1);
	}
	return (0);
}

void	adding_variables(char **tokens)
{
	char	*temp_variable;
	char	*temp_path;
	int		i;
	int		j;

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
					temp_variable = ft_substr(tokens[i], 0, j);
					temp_path = ft_substr(tokens[i], j + 1,
						ft_strlen(tokens[i]) - 1);
					if (!does_token_match_variable(temp_variable, temp_path))
					{
						temp_variable
							= g_global.local_variable[g_global.count_local++];
						temp_path
							= g_global.local_path[g_global.count_local++];
					}
					j = -1;
					break ;
				}
			}
		}
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
