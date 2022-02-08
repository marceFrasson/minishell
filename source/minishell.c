/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:02:03 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/07 22:31:45 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void    loop(void)
{
    char        *input_line;
    char        **tokens;
    t_command   *command_list;

    command_list = NULL;
    while (1)
    {
        //set_sigaction();
        if (take_input(&input_line))
            continue ;
        tokens = split_line(input_line);
		if (check_syntax_error1(tokens) || check_syntax_error2(tokens))
		{
			ft_free_split(tokens);
			free(input_line);
			continue ;
		}
        separate_per_pipes(tokens, &command_list);
		//command_list.command_block = separate_redirects(&command_list.command_block);
        //print_tokens(tokens);
		ft_free_split(tokens);
        // parse_commands(command_list);
        // print_command_list(command_list);
        free_command_list(&command_list);
        free(input_line);
        //print_envp();
        // exec_commands();
    }
}

int main(int argc, char *argv[], char *envp[])
{
	parse_envp(envp);
	loop();
	return (0);
}