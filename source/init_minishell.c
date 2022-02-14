/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:49:50 by ebresser          #+#    #+#             */
/*   Updated: 2022/02/13 22:38:51 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void init_g_struct(void)
{
	g_global.env_variable = NULL;
    g_global.env_path = NULL;
    g_global.local_variable = NULL;
    g_global.local_path = NULL;
	g_global.last_input = NULL;
	g_global.cmd_path = NULL;
    g_global.head  = NULL;
	init_cmd_path();
}

int init_cmd_path(void)
{
	int i;

	g_global.cmd_path = ft_split(getenv("PATH"), ':');
	i = 0;
	while(g_global.cmd_path[i] != NULL)
	{
		ft_strjoin_handled(&(g_global.cmd_path[i]), "/"); //tratada: libera string antiga
		printf("%s\n", g_global.cmd_path[i]);
		i++;
		
	}
	return 0;
}

