/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:59:46 by ebresser          #+#    #+#             */
/*   Updated: 2022/02/13 22:18:40 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int free_cmd_path(void)
{
	int i;

	i = 0;
	while(g_global.cmd_path != NULL && ( (g_global.cmd_path)[i] != NULL ))
	{		
		free((g_global.cmd_path)[i]);		
		(g_global.cmd_path)[i] = NULL;
		i++;
	}
	if (g_global.cmd_path != NULL)
	{		
		free(g_global.cmd_path);		
		g_global.cmd_path = NULL;
	}		
	return 0;
}