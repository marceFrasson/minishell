/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:12:07 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/07 21:59:48 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	search_variable(char *variable)
{
	int i;

	i = -1;
	while (g_global.variable[++i])
	{
		if (ft_strcmp(g_global.variable[i], variable))
			break ;
	}
	return (i);
}

char 	change_dir_to_path(char *path)
{
	int	i;

	i = chdir(path);
	if (i)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (errno);
	}
}

void	change_dir_to_oldpwd(void)
{
	int i;

	i = search_variable("OLDPWD");
	change_dir_to_path(g_global.path[i]);
}

void	change_dir_to_home(void)
{
	int i;

	i = search_variable("HOME");
	change_dir_to_path(g_global.path[i]);
}

void	command_cd(char **args)
{
	char *path;

	path = args[1];
	if (args[2])
	{
		ft_putendl_fd("Minishell: cd: too many arguments", 2);
		g_global.status = 1;
	}
	if (!path || ft_strcmp(path, "~") == 0)
	{
		change_dir_to_home();
		return ;
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		change_dir_to_oldpwd();
		return ;
	}
	else
	{
		change_dir_to_path(path);
		return ;
	}
}