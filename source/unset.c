/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:34:39 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/09 15:48:14 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_unset(char **tokens)
{
	int		status;
	int		i;

	i = 0;
	status = 0;
	while (tokens[++i])
	{
		if (ft_strchr(tokens[i], '='))
		{
			ft_putstr_fd("Minishell: unset: `", 2);
			ft_putstr_fd(tokens[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			status = 1;
		}
		else
			delete_variable(tokens[i], IS_ENV);
	}
	g_global.status = status;
}
