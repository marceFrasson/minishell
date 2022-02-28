/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:25:43 by ebresser          #+#    #+#             */
/*   Updated: 2022/02/28 12:56:32 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_execve(t_command *command_list, char *envp[])
{
	char *path_aux;
	int i;

	path_aux = NULL;
	i = 0;   
	while (g_global.cmd_path[i])
    {
    	path_aux = ft_strjoin(g_global.cmd_path[i], command_list->command_block[0]);
    	if (execve(path_aux, command_list->command_block, envp) < 0 )
		{
			if (path_aux)
			{
				free(path_aux);
				path_aux = NULL;
			}								
    		i++;
		}
    }
	printf("%s: command not found\n", command_list->command_block[0]);
	if (path_aux)
		free(path_aux);
}
void no_pipe_syscmd(t_command *command_list, char *envp[])
{
	pid_t	chlpid;
	int		wstatus;	
	
	chlpid = fork();
	if (chlpid < 0)
	{
		perror("Fork failed");
		exit_minishell(FAILURE);
	}
	if (chlpid == 0) 
	{
		printf("\n\nCMD RESULT:\n-------------\n");//_________________________________debug
		ft_execve(command_list, envp); 
		exit (FAILURE); 
	}
	else
		waitpid(chlpid, &wstatus, 0); //wait(&wstatus);	
}
int exec_without_pipes(t_command *command_list, char *envp[])
{
	int builtin_code;

	builtin_code = which_builtin(command_list);
	printf("built_in code: %d\n\n", builtin_code);
	if (builtin_code)
		do_builtins(command_list, builtin_code);
	else			
		no_pipe_syscmd(command_list, envp);//call system programs
	return SUCCESS; //tratar erros
}


int exec_with_pipes(t_command *command_list, int n_pipes, char *envp[])
{
	int id; 
    int fd[n_pipes][2];
    int pid[n_pipes + 1];
	t_command *ptr_cmd_list;

	open_pipes(n_pipes, fd);		
	id = 0;
	while (id < n_pipes + 1)
	{
		pid[id] = fork();		
		if (pid[id] < 0)
		{
			perror("fork");
			return FAILURE;
		}			
		if (pid[id] == 0)
		{	
			signal(SIGINT, SIG_DFL);
			ptr_cmd_list = select_cmd(id, command_list);
			scope_pipe_select(id, n_pipes, fd);				
			if (id == n_pipes) //debug
				printf("\n\nCMD RESULT:\n-------------\n");
			/* Preciso decidir se é builtin ou 
			 * sys_cmd. Sys_cmd, ok, execve finaliza proc
			 * mas built in necessita matarmos o proc!
			 */			
			ft_execve(ptr_cmd_list, envp);				
			exit (FAILURE);	
		}
		id++;
	}		
	main_process_handler(pid, n_pipes, fd);	
	return SUCCESS;//tratar erros
}

int exec_commands(t_command *command_list, int n_pipes, char *envp[])
{		
	printf("n_pipes: %d\n", n_pipes); //_________________________________debug
	if (n_pipes == 0)
		exec_without_pipes(command_list, envp);
	else
		exec_with_pipes(command_list, n_pipes, envp);
	return SUCCESS;//tratar erros
}	
	