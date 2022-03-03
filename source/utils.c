/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:25:27 by mfrasson          #+#    #+#             */
/*   Updated: 2022/03/03 00:03:05 by mfrasson         ###   ########.fr       */
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

void	free_command_list(t_command **command)
{
	t_command	*temp1;
	t_command	*temp2;

	if (!command)
		return ;
	temp1 = *command;
	while (temp1)
	{
		free_tokens(temp1->command_block);
		temp1 = temp1->next;
	}
	temp1 = *command;
	while (temp1)
	{
		temp2 = temp1->next;
		free(temp1);
		temp1 = temp2;
	}
	*command = NULL;
}

// void	free_command_list(t_command *command)
// {
// 	t_command	*temp;

// 	if (!command)
// 		return ;
// 	while (command)
// 	{
// 		free_tokens(command->command_block);
// 		command = command->next;
// 	}
// 	temp = command;
// 	while (temp)
// 	{
// 		temp = command->next;
// 		free(command);
// 		command = temp;
// 	}
// 	command = NULL;
// }

// void	free_split_of_split(char **str)
// {
// 	int	i;

// 	i = -1;
// 	if (!(str))
// 		return ;
// 	while (*(str + ++i) != NULL)
// 	{
// 		free(*(str + i));
// 		*(str + i) = NULL;
// 	}
// }

// void	free_command(void *command)
// {
// 	if (((t_command *)command)->args)
// 		free_split_of_split(((t_command *)command)->args);
// 	free(command);
// }

// void	free_command_list(void **command)
// {
// 	t_command	*temp;

// 	if (!command)
// 		return ;
// 	temp = ((t_command *)command);
// 	while (command)
// 	{
// 		if (((t_command *)command)->command_block)
// 			free_split_of_split(((t_command *)command)->command_block);
// 		free(command);
// 		command = NULL;
// 		command = temp->next;
// 		temp = temp->next;
// 	}
// }