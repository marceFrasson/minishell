/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:02:03 by mfrasson          #+#    #+#             */
/*   Updated: 2022/03/08 22:20:35 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**split_line(char *input_line, t_command **command_list)
{
	char	**string_array;
	char	*line;

	line = look_for_redirections_and_pipe(input_line);
	string_array = look_for_quotes_and_split(line);
	// printf("\n%s ----- %p\n", input_line, input_line);
	// printf("%s ----- %p\n\n", line, line);
	// return (NULL);
	// adding_variables(string_array);
	print_tokens(string_array, 't');
	separate_per_pipes(string_array, command_list);
	// print_command_list(*command_list);
	remove_token_quotes(*command_list);
	print_command_list(*command_list);
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
	//add_history(buffer);
	put_on_history(buffer);
	input_line[0] = buffer;
	return (0);
}

void    loop(char *envp[])
{
    char        *input_line;
    char        **tokens;	
	int			n_pipes;
    t_command   *command_list;

	command_list = NULL;
	init_g_struct();
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		// set_sigaction();
		if (take_input(&input_line))
			continue ;
		tokens = split_line(input_line, &command_list);
		if (check_syntax_error1(tokens) || check_syntax_error2(tokens))
		{
			free(tokens);
			continue ;
		}
		// command_list.command_block = separate_redirects(&command_list.command_block);
		// print_tokens(tokens);
		// print_command_list(g_global.head);
		// command_list = g_global.head;
		// parse_command_block(command_list->command_block);
		n_pipes = command_list_len(command_list) - 1;
        exec_commands(command_list, n_pipes, envp);
		
		
		free_command_list(&command_list);
		free(input_line);
		free_tokens(tokens);
		// print_envp();
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
	loop(envp);
	
	return (0);
}
