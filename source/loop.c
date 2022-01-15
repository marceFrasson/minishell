/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 11:51:03 by itaureli          #+#    #+#             */
/*   Updated: 2022/01/15 12:07:03 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



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

char	**null_char_array(char **array)
{
	int i;

	i = -1;
	while(array[++i])
		array[i] = NULL;
	return (array);
}

/*
void    print_envp(void)
{
	int i = -1;
	while(++i < g_global.count)
		printf("var: %s\npath: %s\n", g_global.envp_variable[i], g_global.envp_path[i]);
}
// essa print command list so imprime lixo de memoria

void	print_command_list(t_command *command_list)
{
	int i;

	i = 0;
	while(command_list)
	{
		while(command_list->command_block[i])
		{
			printf("%i: %s\n", i, command_list->command_block[i]);
			i++;
		}
		command_list = command_list->next;
	}
}
*/

t_command	*create_new_node(char **command_block, int count)
{
	t_command *new_node;
	int i;

	i = -1;
	new_node = (t_command *)malloc(sizeof(t_command));
	new_node->command_block = (char **)malloc(sizeof(char) * count);
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
	command_block = (char **)malloc(sizeof(char *) * g_global.count);
	while(tokens[i])
	{
		printf("toki: %s\n", tokens[i]);
		if(tokens[i][0] == '|')
		{
			while(j < i)
			{
				printf("antes do command strdup\n");
				command_block[k] = ft_strdup(tokens[j]);
				j++;
				k++;
			}
			printf("antes do create new node\n");
			command_list->next = create_new_node(command_block, k);
			j = i + 1;
			k = 0;
			printf("antes do ->next\n");
			command_list = command_list->next;
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
	printf("fora do while\n");
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

void    loop(void)
{
	char *input_line;
	char **tokens;
	t_command *command_list;

	g_global.first_command = command_list;
	command_list = (t_command *)malloc(sizeof(t_command));
	while(1)
	{
		//set_sigaction();
		if(take_input(&input_line))
			continue ;
		tokens = split_line(input_line);
		separate_per_pipes(tokens, command_list);
		// parse_commands(tokens);
		// print_tokens(tokens);
		// print_command_list(command_list);
		free(input_line);
		//print_envp();
		// exec_commands();
	}
}
