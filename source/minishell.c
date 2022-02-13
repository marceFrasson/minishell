/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:02:03 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/13 20:41:22 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    **split_line(char *input_line)
{
	char    **string_array;
	char    *line;

	line = look_for_redirections_and_pipe(input_line);
	string_array = look_for_quotes_and_split(line);
	//adding_variables(string_array);
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
	//add_history(buffer);
	put_on_history(buffer);
	input_line[0] = buffer;
	return (0);
}

void    loop(void)
{
    char        *input_line;
    char        **tokens;
    t_command   *command_list;

    command_list = NULL;
	g_global.last_input = NULL;//lilangbr
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
        print_command_list(command_list);


		//printf("\n\n%s ", g_global.env_variable[0]);
		//printf(": %s\n", g_global.env_path[0]);
//
		//printf("\n\n%s ", g_global.env_variable[1]);
		//printf(": %s\n", g_global.env_path[1]);
//
		//printf("\n\n%s ", g_global.env_variable[2]);
		//printf(": %s\n", g_global.env_path[2]);


        free_command_list(&command_list);
        free(input_line);
        //print_envp();


        // exec_commands();


    }
}

int main(int argc, char *argv[], char *envp[])
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
