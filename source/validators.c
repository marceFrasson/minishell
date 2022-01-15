/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 11:37:34 by itaureli          #+#    #+#             */
/*   Updated: 2022/01/15 12:02:15 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*insert_space(char *line, int i)
{
	char    *first_join;
	char    *second_join;
	char    *first_part;
	char    *second_part;
	char    *string_ready;
	char    operator;

	first_part = malloc(sizeof(char *) * i + 1);
	second_part = malloc(sizeof(char *) * (ft_strlen(line) + 1));
	first_join = malloc(sizeof(char *) * i + 1);
	string_ready = malloc(sizeof(char *) * (ft_strlen(line) + 1));

	first_part = ft_substr(line, 0, i);
	operator = line[i];
	second_part = ft_substr(line, i + 1, ft_strlen(line) - 1);
	first_join = ft_strjoin(first_part, " ");
	second_join = ft_charjoin(first_join, operator);
	string_ready = ft_strjoin(second_join, second_part);

	free(first_part);
	free(second_part);
	free(first_join);

	return(string_ready);
}

int	check_syntax(char **tokens)
{
	int i;

	i = -1;
	if(tokens[0][0] == '|')
		return (0);
	while(tokens[++i])
	{
		if(is_operator(tokens[i][0]) && is_operator(tokens[i + 1][0]))
			return (0);
	}
	return (1);
}

int	is_operator(char arg)
{
	if (arg == '|')
		return (1);
	else if(arg == '<' || arg == '>')
	{
		if((arg - 1 != '<') || (arg - 1 != '>'))
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int count_tokens(char *line)
{
	int     i;
	int     space_count;
	int     single_quote_status;
	int     double_quote_status;

	i = -1;
	space_count = 0;
	single_quote_status = OFF;
	double_quote_status = OFF;
	while(line[++i])
	{
		if (line[i] == '\'')
		{
			if(single_quote_status)
				single_quote_status = OFF;
			else if (!single_quote_status && !double_quote_status)
				single_quote_status = ON;
		}
		else if(line[i] == '\"')
		{
			if(double_quote_status)
				double_quote_status = OFF;
			else if (!double_quote_status && !single_quote_status)
				double_quote_status = ON;
		}
		if(line[i] == ' ' && (!single_quote_status && !double_quote_status))
			space_count++;
	}
	return (space_count + 1);
}

char **look_for_quotes_and_split(char *line)
{
	int     i;
	int     j;
	int     single_quote_status;
	int     double_quote_status;
	int     last_position;
	char    **line_array;

	i = -1;
	j = 0;
	single_quote_status = OFF;
	double_quote_status = OFF;
	last_position = 0;
	line_array = malloc(sizeof(char *) * (count_tokens(line) + 1));
	line_array[count_tokens(line)] = NULL;
	while(line[++i])
	{
		if (line[i] == '\'')
		{
			if(single_quote_status)
				single_quote_status = OFF;
			else if (!single_quote_status && !double_quote_status)
				single_quote_status = ON;
		}
		else if(line[i] == '\"')
		{
			if(double_quote_status)
				double_quote_status = OFF;
			else if (!double_quote_status && !single_quote_status)
				double_quote_status = ON;
		}
		else if(line[i] == ' ' && (!single_quote_status && !double_quote_status))
		{
			line_array[j++] = ft_substr(line, last_position, i - last_position);
			last_position = i + 1;
		}
	}
	line_array[j++] = ft_substr(line, last_position, i - last_position);
	return (line_array);
}

char *look_for_redirections_and_pipe(char *line)
{
	int i;
	int single_quote_status;
	int double_quote_status;

	i = -1;
	single_quote_status = OFF;
	double_quote_status = OFF;
	while(line[++i])
	{
		if (line[i] == '\'')
		{
			if(single_quote_status)
				single_quote_status = OFF;
			else if (!single_quote_status && !double_quote_status)
			{
				if(i != 0 && line[i - 1] != ' ')
					line = insert_space(line, i);
				single_quote_status = ON;
			}
			i++;
		}
		else if(line[i] == '\"')
		{
			if(double_quote_status)
				double_quote_status = OFF;
			else if (!double_quote_status && !single_quote_status)
			{
				if(i != 0 && line[i - 1] != ' ')
					line = insert_space(line, i);
				double_quote_status = ON;
			}
			i++;
		}
		else if(is_operator(line[i])
			&& (!single_quote_status && !double_quote_status))
		{
			if(i != 0 && (line[i - 1] != ' ' && !((line[i] == '<' && line[i - 1] == '<')
				|| (line[i] == '>' && line[i - 1] == '>'))))
				line = insert_space(line, i);
		}
		else
		{
			if((i != 0 && (is_operator(line[i - 1])
				&& (!single_quote_status && !double_quote_status)))
				&& line[i] != ' ')
				line = insert_space(line, i);
		}
	}
	return (line);
}
