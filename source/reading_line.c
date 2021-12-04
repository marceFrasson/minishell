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

char	*ft_charjoin(char const *string1, char const c)
{
	char	*string;
	int		i;
	int		end_string1;

	if (!string1 || !c)
		return (NULL);
	string = (char *)malloc(((ft_strlen(string1)) + 2));
	if (string == NULL)
		return (NULL);
	i = 0;
	while (string1[i] != '\0')
	{
		string[i] = string1[i];
		i++;
	}
	end_string1 = i;
	i = 0;
	while (c != '\0')
	{
		string[end_string1 + i] = c;
		i++;
	}
	string[end_string1 + i] = '\0';
	return (string);
}

char	*ft_substr_shrink(char const *string, unsigned int start, size_t len)
{
	char	*temp;

	if (!(string))
		return (NULL);
	if (len > (size_t)ft_strlen(string))
		len = ft_strlen(string);
	temp = malloc((len + 1) * sizeof(char));
	if (!(temp))
		return (NULL);
	if (len == 0 || start >= (unsigned int)ft_strlen(string))
	{
		*temp = '\0';
		return (temp);
	}
	ft_strlcpy(temp, (const char *)(string + start), len + 1);
	return (temp);
}

char	*ft_addchar(char *str, char c)
{
	char	*temp;
	int		i;

    i = -1;
	if (!str)
		temp = malloc(2 * sizeof(char));
	else
		temp = malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!temp)
		return (NULL);
	if (str)
	{
		while (str[++i])
			temp[i + 1] = str[i];
		free(str);
	}
	temp[0] = c;
	temp[i + 1] = '\0';
	return (temp);
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



static char	*insert_space(char *line, int i)
{
    char    *first_join;
    char    *string_ready;
    char    *first_part;
    char    *second_part;
    char    operator1;

    first_part = malloc(sizeof(char *) * i + 1);
    printf("i: %i\n", i);
    second_part = malloc(sizeof(char *) * (ft_strlen(line) + 1));
    first_join = malloc(sizeof(char *) * i + 1);
    string_ready = malloc(sizeof(char *) * (ft_strlen(line) + 1));

    first_part = ft_substr(line, 0, i);
    operator1 = line[i];
    //printf("\nline: %s\n", line);
    printf("\nfirst line: %c\n", operator1);
    second_part = ft_substr(line, i + 2, ft_strlen(line) - 1);
    //printf("\nsecond line: %s\n", second_part);
    //printf("\nline2: %s\n", line);
    printf("%s\n", first_part);
	first_join = ft_charjoin(first_part, ' ');
    //string_ready = ft_charjoin(first_join, operator1);

    printf("string ready: %s\n", string_ready);
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
        {
            space_count++;
        }
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
    line_array = malloc(sizeof(char *) * count_tokens(line) + 1);
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
        {
            line_array[j++] = ft_substr(line, last_position, i - last_position);
            last_position = i + 1;
        }
        if(is_operator(line[i]))
        {
            line_array[j++] = &line[i];
            last_position = i + 2;
        }
    }
    line_array[j++] = ft_substr(line, last_position, i - last_position);
    return (line_array);
}

void look_for_redirections_and_pipe(char *line)
{
    int i;

    i = -1;
    while(line[++i])
    {
        if(is_operator(line[i]))
        {
            if(line[i - 1] != ' ')
                line = insert_space(line, i);
            if(line[i + 1] != ' ')
                line = insert_space(line, i);
        }
    }
}

char    **split_line(char *line)
{
    char        **string_array;

    look_for_redirections_and_pipe(line);
    string_array = look_for_quotes_and_split(line);
    return (string_array);
}

char	**split_tokenizer(char *line)
{
    char **tokens;

	tokens = split_line(line);
	//check_syntax_error();
	//tokenizer();
    return (tokens);
}

void    print_tokens(char **tokens)
{
    int i;

    i = -1;
    while(tokens[++i])
    {
        printf("%s\n", tokens[i]);
    }
}

void    loop(void)
{
    char *input_line;
    char **tokens;

    while(1)
    {
        //set_sigaction();
        input_line = read_line();
        tokens = split_tokenizer(input_line);
        //print_tokens(tokens);
        //exec_commands();
    }
}

int main(int argc, char *argv[], char *envp[])
{
    loop();
    return (0);
}

//parse_envp();