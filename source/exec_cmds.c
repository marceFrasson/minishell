/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:25:43 by ebresser          #+#    #+#             */
/*   Updated: 2022/02/21 20:13:24 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void exit_minishell(int reason)
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


static int which_builtin(t_command *command_list)
{ 
	printf("cmd_block[0] = %s\n",command_list->command_block[0] );
	//exit
	if (!ft_strcmp(command_list->command_block[0], "exit") && (command_list->command_block[1] == NULL)) //shell aceita exit "numero"
	{
		free_command_list(&command_list);
		return EXIT;
	}				
	//cd
	else if (!ft_strcmp(command_list->command_block[0], "cd") && command_list->command_block[2] == NULL)
		return CD;
	// ...
		
	//se for built in, retorna int code -> serve para triar em do_builtin
	//caso contrario, retorna 0: N é builtin			
	return 0; 
}
static void do_builtins(t_command *command_list, int code)
{ 
	int status;
	if (code == EXIT)
		exit_minishell(SUCCESS);
	
	if (code == CD)
	{
		status = chdir(command_list->command_block[1]);
		if (status == -1) 
			perror(command_list->command_block[1]);		
	}	
}
static void ft_execve(t_command *command_list, char *envp[])
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
static void system_program(t_command *command_list, char *envp[])
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
		ft_execve(command_list, envp); 
		exit (1); 
	}
	else
	{
		waitpid(chlpid, &wstatus, 0); //wait(&wstatus);	
	}		
}
static int exec_without_pipes(t_command *command_list, char *envp[])
{
	int builtin_code;

	builtin_code = which_builtin(command_list);
	printf("built_in code: %d\n\n", builtin_code);
	if (builtin_code)
		do_builtins(command_list, builtin_code);
	else			
		system_program(command_list, envp);//call system programs
	return 0;
}

static int file_descriptor_handler(int in, int out)
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
    return (0);
}

int exec_commands(t_command *command_list, int n_pipes, char *envp[])
{
	int id, j; 
    int fd[n_pipes][2];
    int pid[n_pipes + 1]; 
	//int wait[n_pipes + 1];
	t_command *ptr_cmd_list;

	ptr_cmd_list = command_list;
	


	//n_pipes = command_list_len(command_list) - 1; 	
	printf("n_pipes: %d\n", n_pipes);
	if (n_pipes == 0)
		exec_without_pipes(command_list, envp);
	else
	{
		
		id = 0;
    	while (id < n_pipes) //vai abrindo os pipes
    	{
    	    if (pipe(fd[id++]) < 0) //deu ruim, libera anteriores
    	    {
				perror("pipe");
    	        j = 0;
    	        while (j < id)
    	        {
    	            close(fd[j][0]);					
    	            close(fd[j][1]);
    	            j++;
    	        }
    	        exit (1);
    	    }
    	    //id++;
    	}
		///////////////////////////////////////

		int fd_in;
		int fd_out;
		id = 0;
		while (id < n_pipes + 1)
		{
			pid[id] = fork();		
			if (pid[id] < 0)
			{
				perror("fork");
				return 2;
			}			
			if (pid[id] == 0)
			{	
				signal(SIGINT, SIG_DFL);

				if (id == 1)
					ptr_cmd_list = ptr_cmd_list->next;
				if (id == 2)
				{
					ptr_cmd_list = ptr_cmd_list->next;
					ptr_cmd_list = ptr_cmd_list->next;
				}
					

				//tratamento demais pipes ::::::::::::::::::::::::::::::::::::::::
    	    	j = 0;
    	    	//fechando escritas de outros pipes
    	    	while (j < n_pipes)
        		{
        		    if (j != id) //pulo o id
        		        close(fd[j][1]);
        		    j++;
					//ultimo: j nunca é igual n_pipe, n fecha no ultimo, nem existe prox pipe
        		}				
    	    	j = 0;
    	    	//fechando leitura
    	    	while (j < n_pipes)
    	    	{
    	    	    if (id != 0 && j != id - 1)  
    	    	        close(fd[j][0]);
    	    	    j++;
					//primeiro n le do pipe, nem existe pipe anterior!
    	    	}	
    	    	//fim tratamento demais pipes :::::::::::::::::::::::::::::
	
	

				if (id != 0 && id != n_pipes)
				{
					fd_in = fd[id - 1][0];
					fd_out = fd[id][1];	
				}
				else if (id == 0)
				{
					close(fd[0][0]);
					fd_in = -1;
					fd_out = fd[0][1];					
				}
				else if (id == n_pipes)
				{
					close(fd[n_pipes - 1][1]);
					fd_in = fd[n_pipes - 1][0];
					fd_out = -1;
				}								
				file_descriptor_handler(fd_in, fd_out);

							
							
				//close(fd[0][0]);
				//dup2(fd[0][1], STDOUT_FILENO); //????????????????????????????????????
				//close(fd[0][1]);

				ft_execve(ptr_cmd_list, envp);				
				//close(fd[0][1]);
				exit (1);	
			}
			id++;
		}
		/*	pid[1] = fork();
			if (pid[1] < 0)
				return 3;
			if (pid[1] == 0)
			{


				ptr_cmd_list = command_list->next;//1
				signal(SIGINT, SIG_DFL);

				dup2(fd[0][0], STDIN_FILENO);
				close(fd[0][0]); 
				close(fd[0][1]); //eu copiei stdin e out!!!!!!!


				//dup2(fd[0][1], STDOUT_FILENO); //stdout vira pipe
				//close(fd[0][1]);

				ft_execve(ptr_cmd_list, envp);
				//close(fd[0][0]);
				exit (1);		 //exit (1); //19fev	
			}
			*/

		//close(fd[0][0]);
    	//close(fd[0][1]);
		///waitpid(pid[0], &wait[0], 0);
		///if (WIFEXITED(wait[0]))
		///{
		///	sleep (5);
		///	kill(pid[1], SIGKILL);//ele n encerra pq espera o pipe1 do primeiro processo fechar
		///}			
		//waitpid(pid[1], NULL, 0);
		j = 0;
		while (j < n_pipes)
		{
			close(fd[j][0]);
			close(fd[j][1]);
			j++;
		}
		id = 0;
		while (id < n_pipes + 1)
		{
			waitpid(pid[id], NULL, 0);
			id++;

		}		


	////	//////////////////////////////////////////////////////////////

	}		
	return 0;
}	
	
	/*
	pid[0] = fork();		
		if (pid[0] < 0)
		{
			perror("fork");
			return 2;

		}			
		if (pid[0] == 0)
		{	
			
			ptr_cmd_list = command_list;//0				
			close(fd[0][0]);
			dup2(fd[0][1], STDOUT_FILENO); //????????????????????????????????????
			close(fd[0][1]);
			
			ft_execve(ptr_cmd_list, envp);				
			//close(fd[0][1]);
			exit (1);	
		}
		pid[1] = fork();
		if (pid[1] < 0)
			return 3;
		if (pid[1] == 0)
		{

			
			ptr_cmd_list = command_list->next;//1
			signal(SIGINT, SIG_DFL);
			
			dup2(fd[0][0], STDIN_FILENO);
			close(fd[0][0]); 
			close(fd[0][1]); //eu copiei stdin e out!!!!!!!

			
			//dup2(fd[0][1], STDOUT_FILENO); //stdout vira pipe
			//close(fd[0][1]);
			
			ft_execve(ptr_cmd_list, envp);
			//close(fd[0][0]);
			exit (1);		 //exit (1); //19fev	
		}
		
		close(fd[0][0]);
    	close(fd[0][1]);
		
		waitpid(pid[0], &wait[0], 0);
		
		//if (WIFEXITED(wait[0]))
		//{
		//	sleep (5);
		//	kill(pid[1], SIGKILL);//ele n encerra pq espera o pipe1 do primeiro processo fechar
		//}			
		waitpid(pid[1], NULL, 0);		
		*/