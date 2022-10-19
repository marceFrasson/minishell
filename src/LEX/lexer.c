/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 13:55:53 by ebresser          #+#    #+#             */
/*   Updated: 2022/10/13 18:26:14 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_syntax(t_data *data)
{
	int		i;

	i = -1;
	while (data->input[++i])
	{
		while (data->input[i] != '|' && data->input[i + 1] != '\0')
			i++;
		if (data->input[i] == '|')
		{
			if (!data->input[i + 1])
			{
				ft_printf(STDERR,
					"Minishell: syntax error near unexpected token `|'\n");
				return (FAILURE);
			}
			else if (data->input[i + 1] == '|')
			{
				ft_printf(STDERR,
					"Minishell: syntax error near unexpected token `||'\n");
				return (FAILURE);
			}
		}
	}
	return (SUCCESS);
}

// Create an aux **str based on pipe
int	pull_pipe(t_data *data)
{
	int	i;

	if (check_pipe_syntax(data))
		return (FAILURE);
	data->cmds_piped = ft_split(data->input, '|');
	if (data->cmds_piped == NULL)
	{
		perror("Minishell: Malloc failed in pull_pipe: ");
		exit_minishell(data, FAILURE);
	}
	data->number_of_pipes = ft_str_count(data->cmds_piped) - 1;
	i = 0;
	while (data->cmds_piped[i])
		unmask_character(data->cmds_piped[i++], 6, '|');
	return (SUCCESS);
}

// Here it gets the format of the argve structure - That's why n returns,
// move directly in the struct
void	pull_space(t_data *data)
{
	int		i;
	int		no_cmds;

	i = 0;
	no_cmds = data->number_of_pipes + 1;
	data->argve = (char ***)ft_calloc((no_cmds + 1), sizeof(char **));
	if (data->argve == NULL)
	{
		perror("Minishell: Malloc failed in pull_space ");
		exit_minishell(data, FAILURE);
	}
	while ((data->cmds_piped)[i])
	{
		data->argve[i] = ft_split((data->cmds_piped)[i], ' ');
		if (data->argve[i] == NULL)
		{
			perror("Minishell: Malloc failed in pull_space ");
			exit_minishell(data, FAILURE);
		}
		i++;
	}
}

int	pull_redirects(t_data *data)
{
	int		id;
	int		redirects_nbr;

	id = 0;
	malloc_file(data, 0, 0, data->number_of_pipes + 2);
	while (data->cmds_piped[id])
	{
		redirects_nbr = count_redirects(data->cmds_piped[id]);
		if (redirects_nbr == -1)
		{
			g_status_code = SINTAX_ERR;
			return (FAILURE);
		}
		malloc_file(data, 1, id, redirects_nbr + 1);
		if (redirects_nbr)
			find_redirects(data, id);
		unmask_character(data->cmds_piped[id], 4, '>');
		unmask_character(data->cmds_piped[id], 5, '<');
		id++;
	}
	return (SUCCESS);
}

int	lexer(t_data *data)
{
	if (pull_quotes(data))
		return (FAILURE);
	if (pull_pipe(data))
		return (FAILURE);
	if (pull_redirects(data))
		return (FAILURE);
	pull_space(data);
	return (SUCCESS);
}
