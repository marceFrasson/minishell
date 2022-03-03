/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_g_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:31:53 by ebresser          #+#    #+#             */
/*   Updated: 2022/03/02 23:41:22 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_command_path(void)
{
	int i;

	i = 0;
	while(g_global.command_path != NULL && ( (g_global.command_path)[i] != NULL ))
	{		
		free((g_global.command_path)[i]);		
		(g_global.command_path)[i] = NULL;
		i++;
	}
	if (g_global.command_path != NULL)
	{		
		free(g_global.command_path);//The free() function returns no value.	
		g_global.command_path = NULL;
	}
}
void free_env_var(void)
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
}

void free_env_path(void)
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
}


void free_local_var(void)
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
}

void free_local_path(void)
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
}