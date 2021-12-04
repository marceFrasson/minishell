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

char    *ft_strcopy(char *src, char *dst)
{
    int i;

    i = 0;
    while (src[i])
    {
        dst[i] = src[i];
        i++;
    }
    return (dst);
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

void read_line(void)
{
    char *line_read;
    char *prompt;

    line_read = (char *)NULL;
    prompt = create_prompt();
    line_read = readline(prompt);

    if (line_read && *line_read)
        add_history(line_read);
}

static void	insert_spaces(char **line, int *i, int ind)
{
    char *temp;

	temp = ft_addchar(line[i], " ");
    ft_strcopy(temp, line[i]);
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

int look_for_quotes_and_split(HIST_ENTRY *line)
{
    int i;
    int j;
    char **line_array;

    i = -1;
    j = -1;
    while(line[++i])
    {
        if (ft_strcmp(line[i], "\'"))
        {
            if(s_quote_on)
                s_quote_on = 0;
            else if (!s_quote_on && !d_quote_on)
                s_quote_on = 1;
        }
        else if(ft_strcmp(line[i], "\""))
        {
            if(d_quote_on)
                d_quote_on = 0;
            else if (!d_quote_on && !s_quote_on)
                d_quote_on = 1;
        }
        else if(ft_strcmp(line[i], " ")) && (s_quote_on = 0 && d_quote_on = 0))
            line[++j] = ft_substr(line, 0, i + 1);
    }
    return (&line_array);
}

int look_for_redirections_and_pipe(HIST_ENTRY *line)
{
    int i;

    i = -1;
    while(line[++i])
    {
        if(is_operator(line[i]))
        {
            if(!ft_strcmp(line[i - 1], " "))
                insert_space(line[i - 1]);
            if(!ft_strcmp(line[i + 1], " "))
                insert_space(line[i]);
        }
    }
}

char    **split_line(void)
{
    HIST_ENTRY *line;
    char **string_array;

    line = history_get(1);
    look_for_redirections_and_pipe(&line);
    string_array = look_for_quotes_and_split(&line);
    
    return (string_array);
}

void	split_tokenizer(void)
{
	split_line();
	check_syntax_error();
	tokenizer();
}

void    loop(void)
{
    set_sigaction();
    read_line();
    split_tokenizer();
    exec_commands();
}

int main(int argc, char *argv[], char *envp[])
{
    if (argc != 1)
        return (0);
    loop();
}
    parse_envp();