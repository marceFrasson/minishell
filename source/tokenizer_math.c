/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_math.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:17:08 by mfrasson          #+#    #+#             */
/*   Updated: 2022/03/02 18:53:22 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_middle_quotes(char **command_block, int j)
{
	char    *first_part;
    char    *temp;

    first_part = ft_substr(*command_block, 0, j);
    temp = ft_strjoin(first_part, *command_block + j + 1);
    free(*command_block);
    free(first_part);
    *command_block = temp;
}

void	remove_token_quotes(t_command *command_list)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (command_list->command_block[i])
	{
		if (command_list->command_block[i][0] == '\''
			|| command_list->command_block[i][0] == '\"')
			command_list->command_block[i] = ft_substr(command_list->command_block[i], 1,
				ft_strlen(command_list->command_block[i]) - 2);
		while (command_list->command_block[i][j] != '\0')
		{
			if (command_list->command_block[i][j] == '\''
				|| command_list->command_block[i][j] == '\"')
				remove_middle_quotes(command_list->command_block, j);
			j++;
		}
		j = 0;
		i++;
	}
	if (command_list->next)
	{
		command_list = command_list->next;
		remove_token_quotes(command_list);
	}
}

int	count_tokens(char *line)
{
	int	i;
	int	space_count;
	int	single_quote_status;
	int	double_quote_status;

	i = -1;
	space_count = 0;
	single_quote_status = OFF;
	double_quote_status = OFF;
	while (line[++i])
	{
		if (line[i] == '\'')
		{
			if (single_quote_status)
				single_quote_status = OFF;
			else if (!single_quote_status && !double_quote_status)
				single_quote_status = ON;
		}
		else if (line[i] == '\"')
		{
			if (double_quote_status)
				double_quote_status = OFF;
			else if (!double_quote_status && !single_quote_status)
				double_quote_status = ON;
		}
		if (line[i] == ' ' && (!single_quote_status && !double_quote_status))
			space_count++;
	}
	g_global.token_count = space_count + 1;
	return (space_count + 1);
}

static char	*insert_space(char *line, int *i)
{
	char	*temp;
	char	*first_part;
	char	*string_ready;

	first_part = ft_substr(line, 0, i[0]);
	if (i[0])
		if (line[i[0] - 1] != ' ')
		{
			temp = first_part;
			first_part = ft_charjoin(temp, ' ');
			free(temp);
		}

	temp = first_part;
	first_part = ft_charjoin(temp, line[i[0]]);
	free(temp);
	if ((line[i[0]] == '<' && line[i[0] + 1] == '<' )
		|| (line[i[0]] == '>' && line[i[0] + 1] == '>' ))
	{
		temp = first_part;
		first_part = ft_charjoin(temp, line[i[0]]);
		free(temp);
		i[0]++;
	}

	if (line[i[0] + 1] != ' ')
	{
		temp = first_part;
		first_part = ft_charjoin(temp, ' ');
		free(temp);
	}
	string_ready = ft_strjoin(first_part, line + i[0] + 1);
	free(first_part);
	free(line);
	i[0]++;
	return (string_ready);
}

char	**look_for_quotes_and_split(char *line)
{
	int		i[3];
	int		single_quote_status;
	int		double_quote_status;
	char	**line_array;

	i[0] = -1;
	i[1] = 0;
	i[2] = 0;
	single_quote_status = OFF;
	double_quote_status = OFF;
	line_array = malloc(sizeof(char *) * (count_tokens(line) + 1));
	line_array[count_tokens(line)] = NULL;
	while (line[++i[0]])
	{
		if (line[i[0]] == '\'')
		{
			if (single_quote_status)
				single_quote_status = OFF;
			else if (!single_quote_status && !double_quote_status)
				single_quote_status = ON;
		}
		if (line[i[0]] == '\"')
		{
			if (double_quote_status)
				double_quote_status = OFF;
			else if (!double_quote_status && !single_quote_status)
				double_quote_status = ON;
		}
		if (line[i[0]] != ' ' || (line[i[0]] == ' '
				&& (single_quote_status || double_quote_status)))
			i[1]++;
		if (i[1] && ((line[i[0] + 1] == '\0' || (line[i[0] + 1] == ' '
						&& (!single_quote_status && !double_quote_status)))))
		{
			line_array[i[2]++] = ft_substr(line + i[0] + 1 - i[1], 0, i[1]);
			i[1] = 0;
		}
	}
	return (line_array);
}

char	*look_for_redirections_and_pipe(char *line)
{
	int	i;
	int	single_quote_status;
	int	double_quote_status;

	i = -1;
	single_quote_status = OFF;
	double_quote_status = OFF;
	while (line[++i])
	{
		if (line[i] == '\'')
		{
			if (single_quote_status)
				single_quote_status = OFF;
			else if (!single_quote_status && !double_quote_status)
				single_quote_status = ON;
		}
		else if (line[i] == '\"')
		{
			if (double_quote_status)
				double_quote_status = OFF;
			else if (!double_quote_status && !single_quote_status)
				double_quote_status = ON;
		}
		else if (is_operator(line[i])
			&& (!single_quote_status && !double_quote_status))
		{
			line = insert_space(line, &i);
		}
	}
	return (line);
}