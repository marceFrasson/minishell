/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:33:19 by ebresser          #+#    #+#             */
/*   Updated: 2022/02/13 21:42:23 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Esta função foi criada pois é preciso analisar se há comandos repetidos.
 * Comandos adjacentes repetidos são interpretados como únicos no historico.
 * Ex. ls, ls, echo > No historico: ls, echo
 */

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