/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 06:19:41 by itaureli          #+#    #+#             */
/*   Updated: 2021/12/08 06:45:24 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_pipes(char **tokens)
{
	/*
	Check if there's pipe command
	*/
	int i;

	i = 0;
	while (tokens)
	{
		printf("%s\n", tokens[i]);
		i++;
	}
}

// execve
int	exec_commands(char *input_line)
{
	char *fake_tokens[2];

	fake_tokens[0] = "echo";
	fake_tokens[1] = "hello world";

	/*
		if is pipe
		go to pipex_exec
		else
		go to exec
	*/
	check_pipes(fake_tokens);
	return(0);
}
