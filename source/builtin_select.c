/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_select.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:39:37 by ebresser          #+#    #+#             */
/*   Updated: 2022/02/28 16:26:15 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int which_builtin(t_command *command_list)
{ 		
	if (!ft_strcmp(command_list->command_block[0], "echo")) 
		return ECHO;
	else if (!ft_strcmp(command_list->command_block[0], "cd"))
		return CD;
	else if (!ft_strcmp(command_list->command_block[0], "pwd")) 
		return PWD;
	else if (!ft_strcmp(command_list->command_block[0], "export")) 
		return EXPORT;
	else if (!ft_strcmp(command_list->command_block[0], "unset")) 
		return UNSET;
	else if (!ft_strcmp(command_list->command_block[0], "env")) 
		return ENV;
	else if (!ft_strcmp(command_list->command_block[0], "exit") && (command_list->command_block[1] == NULL)) //shell aceita exit "numero"
		return EXIT; //free_command_list(&command_list);
	return NOT_BUILTIN; 
}
int do_builtins(t_command *command_list, int code, int fdout)
{ 	
	//ft_putnbr_fd(code, 2); //DEBUG
	if (code == ECHO)
		command_echo(command_list->command_block, fdout);
	if (code == CD)	
		command_cd(command_list->command_block); //VER TRATAMENTO DE ERROS! (perror)
	if (code == PWD)
		command_pwd(fdout);
	if (code == EXPORT)
		command_export(command_list->command_block);
	if (code == UNSET)
		command_unset(command_list->command_block);
	if (code == ENV)
		command_env();
	if (code == EXIT)
		command_exit(command_list->command_block); //exit_minishell(SUCCESS);
	return SUCCESS;
}