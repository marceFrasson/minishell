/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:33:19 by ebresser          #+#    #+#             */
/*   Updated: 2022/02/13 20:50:59 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void put_on_history(char *buffer)
{	
	if (!g_global.last_input || ft_strcmp(g_global.last_input, buffer))
		add_history(buffer); 
	if (g_global.last_input)
	{					
		free(g_global.last_input);					
		g_global.last_input = NULL;
	}					
	g_global.last_input = ft_strdup(buffer); //atualiza	
}