/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_select.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:39:37 by ebresser          #+#    #+#             */
/*   Updated: 2022/02/28 13:06:34 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int which_builtin(t_command *command_list) //--> apontar depois p codigo da Marce
{ 
	printf("cmd_block[0] = %s\n",command_list->command_block[0] );
	//exit --> apontar depois p codigo da Marce
	if (!ft_strcmp(command_list->command_block[0], "exit") && (command_list->command_block[1] == NULL)) //shell aceita exit "numero"
	{
		free_command_list(&command_list);
		return EXIT;
	}				
	//cd --> apontar depois p codigo da Marce
	else if (!ft_strcmp(command_list->command_block[0], "cd") && command_list->command_block[2] == NULL)
		return CD;				
	return NOT_BUILTIN; 
}
int do_builtins(t_command *command_list, int code)
{ 
	int status;
	if (code == EXIT)
		exit_minishell(SUCCESS);	
	if (code == CD)
	{
		status = chdir(command_list->command_block[1]);
		if (status == -1)
		{
			perror(command_list->command_block[1]);
			return FAILURE;
		}				
	}	
	return SUCCESS;
}