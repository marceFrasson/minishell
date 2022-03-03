/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:25:27 by mfrasson          #+#    #+#             */
/*   Updated: 2022/03/03 02:01:18 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_splitlen(char **str)
{
	int	i;

	i = 0;
	if (!(str))
		return (i);
	while (*(str + i) != NULL)
		i++;
	return (i);
}

void	free_tokens(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i] && i < g_global.token_count - 1)
	{
		free(tokens[i]);
		tokens[i] = NULL;
	}
	free(tokens);
	tokens = NULL;
}

void	free_command(t_command *command)
{
	int i;

	i = -1;
	while (command->command_block[++i] != NULL)
		free(command->command_block[i]);
}

void	free_command_list(t_command **command)
{
	t_command	*temp;

	if (!*command)
		return ;
	temp = *command;
	if ((*command)->command_block)
		free_command(*command);
	free(*command);
	*command = temp->next;
	if (temp->next)
		free_command_list(command);
}



	// printf("\n1 : %s\n\n", (*(command))->command_block[0]);
	// printf("\n2 : %s\n", (*(command))->command_block[0]);
	// printf("\nbefore free : %i\n\n", (*command)->word_count);
	// printf("\n3 : %p\n", *command);
	// printf("3 : %p\n\n", *command);
	// printf("\nafter  free : %i\n\n", (*command)->word_count);
	// printf("\n4 : %s\n\n", (*(command))->command_block[0]);
	// printf("\ncmnd : %p\ntemp : %p\n\n", *command, temp);