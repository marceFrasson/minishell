/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:02:03 by mfrasson          #+#    #+#             */
/*   Updated: 2022/03/02 15:44:05 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**split_line(char *input_line, t_command *command_list)
{
	char	**string_array;
	char	*line;

	line = look_for_redirections_and_pipe(input_line);
	string_array = look_for_quotes_and_split(line);
	adding_variables(string_array);
	// print_tokens(string_array);
	separate_per_pipes(string_array, &command_list);
	// print_command_list(command_list);
	remove_token_quotes(command_list);
	print_command_list(command_list);
	return (string_array);
}

int	take_input(char **input_line)
{
	char	*buffer;
	char	*prompt;

	prompt = create_prompt();
	buffer = readline(prompt);
	free(prompt);
	if (!buffer)
		exit (0); // exit program
	if (buffer[0] == '\0')
	{
		free(buffer);
		return (1);
	}
	add_history(buffer);
	input_line[0] = buffer;
	return (0);
}

void	loop(void)
{
	char		*input_line;
	char		**tokens;
	t_command	*command_list;

	command_list = NULL;
	g_global.head = command_list;
	while (1)
	{
		//set_sigaction();
		if (take_input(&input_line))
			continue ;
		tokens = split_line(input_line, command_list);
		if (check_syntax_error2(tokens) || check_syntax_error1(tokens))
		{
			free_tokens(tokens);
			free(input_line);
			continue ;
		}
		//command_list.command_block = separate_redirects(&command_list.command_block);
		//print_tokens(tokens);
		print_command_list(g_global.head);
		command_list = g_global.head;
		// parse_command_block(command_list->command_block);
		free_command_list(&command_list);
		free(input_line);
		free_tokens(tokens);
		//print_envp();
		// exec_commands();
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc > 1 && *argv)
	{
		ft_putendl_fd("Minishell: Too many arguments", 1);
		return (1);
	}
	parse_envp(envp);
	loop();
	return (0);
}
