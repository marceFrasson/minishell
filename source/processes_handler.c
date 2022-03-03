/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:44:05 by ebresser          #+#    #+#             */
/*   Updated: 2022/03/02 23:41:22 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command* select_command(int id_pid, t_command *command_list)
{
	t_command *aux;
	int count;

	aux = command_list;
	count = 0;
	while(aux != NULL && count < id_pid)
	{
		aux = aux->next;
		count++;
	}
	return aux;
}
int main_process_handler(int *pid, int n_pipes, int fd[n_pipes][2])
{
	int count;
	
	count = 0;
	while (count < n_pipes)
	{
		close(fd[count][0]);
		close(fd[count][1]);
		count++;
	}
	count = 0;
	while (count < n_pipes + 1)
	{
		waitpid(pid[count], NULL, 0);
		count++;
	}
	return SUCCESS;//tratar erros	
}