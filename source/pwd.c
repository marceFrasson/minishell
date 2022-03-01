/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:11:29 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/07 22:32:07 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_pwd(int fdout)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (buffer)
	{
		ft_putendl_fd(buffer, fdout);
		g_global.status = 0;
	}
	else
	{
		ft_putstr_fd("Minishell: pwd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_global.status = errno;
	}
	free(buffer);
}
