/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:59:46 by ebresser          #+#    #+#             */
/*   Updated: 2022/02/28 12:33:32 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void exit_minishell(int reason)
{
	free_cmd_path();
	free_env_var();
	free_env_path();
	free_local_var();
	free_local_path();
	free(g_global.last_input);
	printf("\nExit MINISHELL - Bye!\n");
	exit (reason);
}

