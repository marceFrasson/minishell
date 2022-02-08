/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   X.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:25:27 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/07 21:43:57 by mfrasson         ###   ########.fr       */
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

int	is_operator(char arg)
{
	if (arg == '|')
		return (1);
	else if (arg == '<' || arg == '>')
	{
		if ((arg - 1 != '<') || (arg - 1 != '>'))
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int	is_operators(char *arg)
{
	if (!(ft_strcmp(arg, "|")))
		return (1);
	else if (!(ft_strcmp(arg, "<")) || !(ft_strcmp(arg, ">")))
		return (2);
	else if (!(ft_strcmp(arg, "<<")) || !(ft_strcmp(arg, ">>")))
		return (3);
	else
		return (0);
}

void free_command_list(t_command **command)
{
    t_command *temp1;
    t_command *temp2;

    if (!command)
        return;
    temp1 = *command;
    while (temp1)
    {
        ft_free_split(temp1->command_block);
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
