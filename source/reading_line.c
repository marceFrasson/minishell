/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:04:46 by mfrasson          #+#    #+#             */
/*   Updated: 2022/01/15 15:15:12 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_variable(char *token)
{
	int		i;
	char    *first_part;
	char    *second_part;


	i = 0;
	while(token[i])
	{
		if(token[i] == '=')
		{
			first_part = malloc(sizeof(char *) * i + 1);
			second_part = malloc(sizeof(char *) * ((ft_strlen(token) + 1) - i));

			g_global.envp_variable[g_global.count] = ft_substr(token, 0, i);
			g_global.envp_path[g_global.count] = ft_substr(token, i + 1, ft_strlen(token) - 1);

			free(first_part);
			free(second_part);
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
	while(!ft_strcmp(variable, g_global.envp_variable[i]))
		i++;
	printf("i: %i\n", i);
	return (g_global.envp_path[i]);
}

void    split_envp(char *envp[], int j, int i)
{
	char    *first_part;
	char    *second_part;

	first_part = malloc(sizeof(char *) * i + 1);
	second_part = malloc(sizeof(char *) * ((ft_strlen(envp[j]) + 1) - i));

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

void	remove_token_quotes(char **tokens)
{
	int i;

	i = -1;
	while(tokens[++i])
	{
		if(tokens[i][0] == '\'' || tokens[i][0] == '\"')
			tokens[i] = ft_substr(tokens[i], 1, ft_strlen(tokens[i]) - 2);
	}
}

void	parse_commands(char **tokens)
{
	if(tokens[0][0] == '$')
		tokens[0] = expanding_variable(tokens[0]);
	// if(ft_strcmp(tokens[0], "echo"))
	// 	command_echo(tokens);
	// else if(ft_strcmp(tokens[0], "cd"))
	// 	command_cd();
	// else if(ft_strcmp(tokens[0], "pwd"))
	// 	command_pwd();
	// else if(ft_strcmp(tokens[0], "export"))
	// 	command_export();
	// else if(ft_strcmp(tokens[0], "unset"))
	// 	command_unset();
	// else if(ft_strcmp(tokens[0], "env"))
	// 	command_env();
	// else if(ft_strcmp(tokens[0], "exit"))
	// 	command_exit();
	else if(ft_strchr(tokens[0], '='))
		add_variable(tokens[0]);
	/*else
		error_message?*/
}

char    **split_line(char *input_line)
{
	char    **string_array;
	char    *line;

	line = look_for_redirections_and_pipe(input_line);
	string_array = look_for_quotes_and_split(line);
	remove_token_quotes(string_array);
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
	free(prompt_green);
	free(prompt_reset);
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

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!(new))
		return ;
	else if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = ft_lstlast(*lst);
	new->prev = temp;
	temp->next = new;
}

t_command	*create_new_node(char **command_block, int count)
{
	t_command *new_node;
	int i;

	i = -1;
	new_node = (t_command *)malloc(sizeof(t_command));
	new_node->command_block = malloc(sizeof(char *) * (count + 1));
	new_node->command_block[count] = NULL;
	new_node->next = NULL;
	while(++i < count)
		new_node->command_block[i] = ft_strdup(command_block[i]);
	return (new_node);
}

void	separate_per_pipes(char **tokens, t_command *command_list)
{
	char **command_block;
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	command_block = malloc(sizeof(char *) * g_global.count);
	while(tokens[i])
	{
		if(tokens[i][0] == '|')
		{
			while(j < i)
			{
				command_block[k] = ft_strdup(tokens[j]);
				j++;
				k++;
			}
			command_list->next = create_new_node(command_block, k);
			command_list = command_list->next;
			j = i + 1;
			k = 0;
		}
		i++;
	}
	while(j + 1 <= i)
	{
		command_block[k] = ft_strdup(tokens[j]);
		j++;
		k++;
	}
	command_list->next = create_new_node(command_block, k);
	command_list = command_list->next;
	command_list = g_global.head;
	g_global.head = command_list->next;
	command_list = g_global.head;
}

void	count_word_blocks(t_command *command_list)
{
	int i;
	int word_count;

	i = -1;
	printf("dentro do count blocks\n");
	while(command_list)
	{
		while(command_list->command_block[i]
			&& (!is_operator(command_list->command_block[i][0])
			&& !is_operator(command_list->command_block[i - 1][0])))
		{
			command_list->word_count++;
			i++;
		}
		command_list = command_list->next;
	}
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

void    print_tokens(char **tokens)
{
	int i;
	
	i = -1;
	while(tokens[++i])
		printf("%i: %s\n", i, tokens[i]);
}

void    print_envp(void)
{
	int i = -1;
	while(++i < g_global.count)
		printf("var: %s\npath: %s\n", g_global.envp_variable[i], g_global.envp_path[i]);
}

void	print_command_list(t_command *command_list)
{
	int i;

	i = 1;
	command_list = g_global.head;
	while(command_list)
	{
		write(1, "ini do separete per pipes\n", 27);
		printf("command list: %s\n", command_list->command_block[i]);
		while(command_list->command_block[i])  // <- segfault
		{
			write(1, "fim do separete per pipes\n", 27);
			printf("%i: %s\n", i, command_list->command_block[i]);
			i++;
		}
		command_list = command_list->next;
	}
}

void    loop(void)
{
	char		*input_line;
	char		**tokens;
	t_command	*command_list;

	// g_global.head = command_list;
	// command_list = (t_command *)malloc(sizeof(t_command));
	command_list = NULL;
	while(1)
	{
		//set_sigaction();
		if(take_input(&input_line))
			continue ;
		tokens = split_line(input_line);
		separate_per_pipes(tokens, &command_list);
		// count_word_blocks(command_list);
		// parse_commands(tokens);
		// print_tokens(tokens);
		print_command_list(command_list);
		free(input_line);
		//print_envp();
		// exec_commands();
	}
}

int main(int argc, char *argv[], char *envp[])
{
	//printf("oie aqui eh\n");
	parse_envp(envp);
	loop();
	return (0);
}


// ___________________________________________________________________________________________________________________


/*

	separar os blocos de comandos separados por pipes em uma lista linkada
	contar cada bloco de comandos da lista e contar quantas palavras tem alem do redirect e sua palavra a direita
	criar um array com o numero de palavras
	copiar pra este array as palavras que nao o redirect e sua palavra a direita
	executar o comando e passar seus argumentos
	redirecionar


	cria um fd
	cria um pipefd
	fd[0] = pipefd[0]
	pipe(fd)
	fd[1] = pipefd[1]
	redirect fds
	exec comands(fd[0], fd[1])
	close fd[0]
	close fd[1]

	
	getpath
	getenvp(g_global.envp_variable, g_global.envp_path)
	execv(char *command, char **command_block, envp)


	exec_buitins
	exec_non_builtins
	
	*/