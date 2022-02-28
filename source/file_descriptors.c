/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:04:51 by ebresser          #+#    #+#             */
/*   Updated: 2022/02/28 12:12:51 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int open_pipes(int n_pipes, int fd[n_pipes][2])
{
	int id;
	int j;

	id = 0;
    while (id < n_pipes) //open pipes
    {
        if ((pipe(fd[id++])) < 0)
        {
			perror("pipe");
            j = 0;
            while (j < id)
            {
                close(fd[j][0]);					
                close(fd[j][1]);
                j++;
            }
            exit (1); //tratar
        }
        
    }
	return 0;
}
int close_pipes(int id, int n_pipes, int fd[n_pipes][2])
{
	int j;
	
    j = 0;
    while (j < n_pipes)
    {
        if (j != id)
            close(fd[j][1]);
        j++;
    }				
    j = 0;    
    while (j < n_pipes)
    {
        if (j != id - 1)
            close(fd[j][0]);
        j++;
    }
	return 0; //tratar erros
}
int stdin_stdout_redirect(int in, int out)
{
	if (in != -1)
    {
        dup2(in, STDIN_FILENO);
        close(in);
    }
    if (out != -1)
    {
        dup2(out, STDOUT_FILENO);
        close(out);
    }
	return (0); //tratar erros
}
int file_descriptor_handler(int id, int n_pipes, int fd[n_pipes][2])
{
	int fd_in;
	int fd_out;

	fd_in = 0;
	fd_out = 0;
	if (id == 0)
		fd_in = -1;
	if (id == n_pipes)
		fd_out = -1;
	if (fd_in != -1)
		fd_in = fd[id - 1][0];
	if (fd_out != -1)
		fd_out = fd[id][1];	
	stdin_stdout_redirect(fd_in, fd_out);	
	return 0; //tratar erros
}
int scope_pipe_select(int id, int n_pipes, int fd[n_pipes][2])
{
	close_pipes(id, n_pipes, fd);    
	file_descriptor_handler(id, n_pipes, fd);
	return 0; //tratar erros
}