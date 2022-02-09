/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:24:29 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/09 15:49:55 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    free_variables(void)
{
    free(g_global.env_variable);
    free(g_global.env_path);
}

static int	not_a_number(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (1);
	return (0);
}

static int	select_exit_status(char **args)
{
	if (not_a_number(args[1]))
	{
		ft_putstr_fd("Minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		g_global.status = 2;
		return (1);
	}
	if (args[2])
	{
		ft_putendl_fd("Minishell: exit: too many arguments", 2);
		g_global.status = 1;
		return (0);
	}
	g_global.status = ft_atoi(args[1]);
	return (1);
}

void	command_exit(char **args)
{
	int	status;

	ft_putendl_fd("exit", 2);
	status = 1;
	if (args)
	{
		if (args[1])
			status = select_exit_status(args);
		if (status)
			ft_free_split(args);
	}
	if (status)
	{
		free_variables();
		rl_clear_history();
		exit(g_global.status);
	}
}
