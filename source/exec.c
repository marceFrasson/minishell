/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 06:19:41 by itaureli          #+#    #+#             */
/*   Updated: 2021/12/20 22:33:23 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void check_command(char **tokens)
{
	int i;

	i = 0;
	while (ft_strcmp(tokens[i], "\0") == 0)
	{
		if(ft_strcmp(tokens[i], "echo") == 0)
			printf("run echo builtin");
		else if(ft_strcmp(tokens[i], "cd") == 0)
			printf("run cd builtin");
		else if(ft_strcmp(tokens[i], "pwd") == 0)
			printf("run pwd builtin");
		else if(ft_strcmp(tokens[i], "export") == 0)
			printf("run export builtin");
		else if(ft_strcmp(tokens[i], "unset") == 0)
			printf("run unset builtin");
		else if(ft_strcmp(tokens[i], "env") == 0)
			printf("run env builtin");
		else if(ft_strcmp(tokens[i], "exit") == 0)
			printf("run exit builtin");
		i++;
	}
}

int	check_pipes(char **tokens)
{
	/*
	Check if there's pipe command
	*/
	int i;
	int pipe;

	pipe = 0;
	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|"))
		{
			pipe = 1;
			break ;
		}
		i++;
	}
	return(0);
}

// execve
int	exec_commands(char *input_line)
{
	char *fake_tokens[4];

	fake_tokens[0] = "echo";
	fake_tokens[1] = "hello world";
	fake_tokens[2] = "pwd";
	fake_tokens[3] = "\0";
	/*
		if is pipe
		go to pipex_exec
		else
		go to exec
	*/
	// check_pipes(fake_tokens);
	check_command(fake_tokens);
	return(0);
}
