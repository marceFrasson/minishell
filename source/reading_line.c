/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:04:46 by mfrasson          #+#    #+#             */
/*   Updated: 2021/11/30 17:36:03 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    split_envp(char *envp[], int j, int i)
{
	char    *first_part;
	char    *second_part;

	first_part = malloc(sizeof(char *) * i + 1);
	second_part = malloc(sizeof(char *) * (ft_strlen(envp[j]) + 1));

	g_global.envp_variable[j] = ft_substr(envp[j], 0, i);
	g_global.envp_path[j] = ft_substr(envp[j], i + 1, ft_strlen(envp[j]) - 1);

	free(first_part);
	free(second_part);
}

int count_envp(char *envp[])
{
	int i;

	i = 0;
	while(envp[i])
		i++;
	return (i);
}

void    parse_envp(char *envp[])
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    g_global.count = count_envp(envp);
    g_global.envp_variable = malloc(sizeof(char *) * (g_global.count + 30));
    g_global.envp_path = malloc(sizeof(char *) * (g_global.count + 30));
    while(j < g_global.count)
    {
        if(envp[j][i] == '=')
        {
            split_envp(envp, j, i);
            j++;
            i = 0;
        }
        i++;
    }
}

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
	single_quote_status = 0;
	double_quote_status = 0;
	while(line[++i])
	{
		if (line[i] == '\'')
		{
			if(single_quote_status)
				single_quote_status = 0;
			else if (!single_quote_status && !double_quote_status)
				single_quote_status = 1;
		}
		else if(line[i] == '\"')
		{
			if(double_quote_status)
				double_quote_status = 0;
			else if (!double_quote_status && !single_quote_status)
				double_quote_status = 1;
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
	single_quote_status = 0;
	double_quote_status = 0;
	last_position = 0;
	line_array = malloc(sizeof(char *) * (count_tokens(line) + 1));
	line_array[count_tokens(line)] = NULL;
	while(line[++i])
	{
		if (line[i] == '\'')
		{
			if(single_quote_status)
				single_quote_status = 0;
			else if (!single_quote_status && !double_quote_status)
				single_quote_status = 1;
		}
		else if(line[i] == '\"')
		{
			if(double_quote_status)
				double_quote_status = 0;
			else if (!double_quote_status && !single_quote_status)
				double_quote_status = 1;
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
	single_quote_status = 0;
	double_quote_status = 0;
	while(line[++i])
	{
		if (line[i] == '\'')
		{
			if(single_quote_status)
				single_quote_status = 0;
			else if (!single_quote_status && !double_quote_status)
			{
				if(i != 0 && line[i - 1] != ' ')
					line = insert_space(line, i);
				single_quote_status = 1;
			}
			i++;
		}
		else if(line[i] == '\"')
		{
			if(double_quote_status)
				double_quote_status = 0;
			else if (!double_quote_status && !single_quote_status)
			{
				if(i != 0 && line[i - 1] != ' ')
					line = insert_space(line, i);
				double_quote_status = 1;
			}
			i++;
		}
		else if(is_operator(line[i]) && (!single_quote_status && !double_quote_status))
		{
			if(i != 0 && (line[i - 1] != ' ' && !((line[i] == '<' && line[i - 1] == '<')
				|| (line[i] == '>' && line[i - 1] == '>'))))
				line = insert_space(line, i);
		}
		else
		{
			if(i != 0 && (is_operator(line[i - 1]) && (!single_quote_status && !double_quote_status)))
				line = insert_space(line, i);
		}
	}
	return (line);
}

char    **split_line(char *input_line)
{
	char    **string_array;
	char    *line;

	line = look_for_redirections_and_pipe(input_line);
	string_array = look_for_quotes_and_split(line);
	return (string_array);
}

char    *create_prompt(void)
{
	char	buff[4096];
	char	*prompt_green;
	char	*prompt_reset;
	char	*prompt_full;

	getcwd(buff, sizeof(buff));
	prompt_green = ft_strjoin("\001\033[1;32m\002", buff);
	prompt_reset = ft_strjoin("\001\033[0;0m\002", "$ ");
	prompt_full = ft_strjoin(prompt_green, prompt_reset);
	//free(tudo); // free tudo - prompt-full
	return (prompt_full);
}

char *read_line(void)
{
	char    *line_read;
	char    *prompt;

	line_read = (char *)NULL;
	prompt = create_prompt();
	line_read = readline(prompt);

	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

int take_input(char **input_line)
{
	char    *buffer;
	char    *prompt;

	prompt = create_prompt();
	buffer = readline(prompt);
	free(prompt);
	if(!buffer)
		exit (0); // exit program
	if(buffer[0] == '\0')
	{
		free(buffer);
		return (1);
	}
	add_history(buffer);
	input_line[0] = buffer;
	return (0);
}

void    print_tokens(char **tokens)
{
	int i;
	
	i = -1;
	while(tokens[++i])
		printf("%s\n", tokens[i]);
}

void    loop(void)
{
	char *input_line;
	char **tokens;

	while(1)
	{
		//set_sigaction();
		if(take_input(&input_line))
			continue ;
		tokens = split_line(input_line);
		print_tokens(tokens);
		free(input_line);
		// exec_commands();
	}
}

void    print_envp(void)
{
	int i = -1;
	while(++i < g_global.count)
		printf("var: %s\npath: %s\n", g_global.envp_variable[i], g_global.envp_path[i]);
}

int main(int argc, char *argv[], char *envp[])
{
	//printf("oie aqui eh\n");
	parse_envp(envp);
	loop();
	return (0);
}
