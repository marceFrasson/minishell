/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:09:28 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/09 15:09:46 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_for_operators(char **tokens)
{
	int i;

	i = -1;
	while (tokens[i])
	{
		if (is_operators(tokens[i]))
			return (1);
	}
	return (0);
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
