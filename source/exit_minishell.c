/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:59:46 by ebresser          #+#    #+#             */
/*   Updated: 2022/02/15 00:46:33 by ebresser         ###   ########.fr       */
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
int free_env_var(void)
{
	int i;

	i = 0;
	while(g_global.env_variable != NULL && ( (g_global.env_variable)[i] != NULL ))
	{		
		free((g_global.env_variable)[i]);		
		(g_global.env_variable)[i] = NULL;
		i++;
	}
	if (g_global.env_variable != NULL)
	{		
		free(g_global.env_variable);		
		g_global.env_variable = NULL;
	}		
	return 0;
}

int free_env_path(void)
{
	int i;

	i = 0;
	while(g_global.env_path != NULL && ( (g_global.env_path)[i] != NULL ))
	{		
		free((g_global.env_path)[i]);		
		(g_global.env_path)[i] = NULL;
		i++;
	}
	if (g_global.env_path != NULL)
	{		
		free(g_global.env_path);		
		g_global.env_path = NULL;
	}		
	return 0;
}


int free_local_var(void)
{
	int i;

	i = 0;
	while(g_global.local_variable != NULL && ( (g_global.local_variable)[i] != NULL ))
	{		
		free((g_global.local_variable)[i]);		
		(g_global.local_variable)[i] = NULL;
		i++;
	}
	if (g_global.local_variable != NULL)
	{		
		free(g_global.local_variable);		
		g_global.local_variable = NULL;
	}		
	return 0;
}

int free_local_path(void)
{
	int i;

	i = 0;
	while(g_global.local_path != NULL && ( (g_global.local_path)[i] != NULL ))
	{		
		free((g_global.local_path)[i]);		
		(g_global.local_path)[i] = NULL;
		i++;
	}
	if (g_global.local_path != NULL)
	{		
		free(g_global.local_path);		
		g_global.local_path = NULL;
	}		
	return 0;
}