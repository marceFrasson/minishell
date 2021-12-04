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
			temp[i] = str[i];
		free(str);
	}
	temp[i] = c;
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

static void	insert_space(char *line, int i)
{
    char    *temp;

	temp = ft_addchar(&line[i], ' ');
    ft_strcopy(temp, &line[i]);
}

int	is_operator(char *arg)
{
	if (!(ft_strcmp(arg, "|")))
		return (1);
	else if (!(ft_strcmp(arg, "<")) || !(ft_strcmp(arg, ">")))
		return (2);
	else if (!(ft_strcmp(arg, "<<")) || !(ft_strcmp(arg, ">>")))
		return (3);
	else
		return (0);
}

char **look_for_quotes_and_split(char *line)
{
    int     i;
    int     j;
    int     single_quote_status;
    int     double_quote_status;
    char    **line_array;

    i = -1;
    j = 0;
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
            line_array[j++] = ft_substr(line, 0, i);
            printf("%s\n", line_array[j - 1]);
        }
    }
    return (line_array);
}

void look_for_redirections_and_pipe(char *line)
{
    int i;

    i = -1;
    while(line[++i])
    {
        if(is_operator(&line[i]))
        {
            if(!ft_strcmp(&line[i - 1], " "))
                insert_space(&line[i - 1], i);
            if(!ft_strcmp(&line[i + 1], " "))
                insert_space(&line[i], i);
        }
    }
}

char    **split_line(char *line)
{
    char        **string_array;

    look_for_redirections_and_pipe(line);
    string_array = look_for_quotes_and_split(line);
    
    // int i = -1;
    // while(string_array)
    // {
    //     printf("%s\n", string_array[++i]);
    // }
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
    while(tokens)
    {
        printf("%s", tokens[++i]);
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