/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:34:39 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/07 22:35:12 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_variable(char *arg)
{
	if (!ft_strcmp(g_global.variable, arg))
	{
		
	}
}

void	command_unset(char **args)
{
	int		status;
	int		i;

	i = 0;
	status = 0;
	while (args[++i])
	{
		if (ft_strchr(args[i], '='))
		{
			ft_putstr_fd("Minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			status = 1;
		}
		else
			delete_variable(args[i]);
	}
	g_global.status = status;
}
