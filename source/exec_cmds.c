/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:25:43 by ebresser          #+#    #+#             */
/*   Updated: 2022/02/15 00:59:24 by ebresser         ###   ########.fr       */
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

static int command_list_len(t_command *command_list)
{
	int			len;
	t_command	*ptr;

	len = 0;
	ptr = command_list;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		len++;
	}
	return len;
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
    	printf("%s: command not found\n", command_list->command_block[0]);
		//N precisa encerrar, encerra sozinho e libera mem
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





int exec_commands(t_command *command_list, char *envp[])
{
	int n_pipes, id, j; //Um pipe!!!!!
    int fd[1][2];
    int pid[1 + 1]; 
	int wait[2];
	t_command *ptr_cmd_list;

	n_pipes = command_list_len(command_list) - 1; 	
	printf("n_pipes: %d\n", n_pipes);
	if (n_pipes == 0)
		exec_without_pipes(command_list, envp);
	else
	{
		id = 0;
    	while (id < n_pipes) //vai abrindo os pipes
    	{//abre e ja testa
    	    if (pipe(fd[id]) < 0) //deu ruim, libera anteriores
    	    {
    	        j = 0;
    	        while (j < id)
    	        {
    	            close(fd[j][0]);
    	            close(fd[j][1]);
    	            j++;
    	        }
    	        exit (1);
    	    }
    	    id++;
    	}
	
		pid[0] = fork();
		if (pid[0] < 0)
			return 2;
		if (pid[0] == 0)
		{
			char *path_aux;
			int i;

			signal(SIGINT, SIG_DFL);
			if (n_pipes == 1)
			{
				close(fd[0][0]); 		
				dup2(fd[0][1], STDOUT_FILENO);
				close(fd[0][1]);
			}
		
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
			exit (1);	
		}
	
		if (n_pipes == 1)
		{
			pid[1] = fork();
			if (pid[1] < 0)
				return 3;
			if (pid[1] == 0)
			{
				char *path_aux;
				int i;

				signal(SIGINT, SIG_DFL);
				dup2(fd[0][0], STDIN_FILENO);
				close(fd[0][0]); 
				path_aux = NULL;
				i = 0;
				ptr_cmd_list = command_list->next;
				while (g_global.cmd_path[i])
    			{
    				path_aux = ft_strjoin(g_global.cmd_path[i], ptr_cmd_list->command_block[0]);
    				if (execve(path_aux, ptr_cmd_list->command_block, envp) < 0 )
					{
							if (path_aux)
							{
								free(path_aux);
								path_aux = NULL;
							}								
    						i++;
					}
    			}
				printf("%s: command not found\n", ptr_cmd_list->command_block[0]);
				if (path_aux)
					free(path_aux);
				close(fd[0][1]);
				exit (1);			
			}
		}
		if (n_pipes == 1)
		{
			close(fd[0][0]);
    		close(fd[0][1]);
		}
		waitpid(pid[0], &wait[0], 0);
		if (WIFEXITED(wait[0]))
			kill(pid[0], SIGKILL);
		waitpid(pid[1], NULL, 0);
		//ls -l | grep to
		//sleep(2);
		//kill(pid[0], SIGKILL);
		//kill(pid[1], SIGKILL);
	}	
	
	return 0;
}	
	/*
	int n_pipes, id, j, numero;
    int fd[n_pipes][2];
    int pid[n_pipes + 1]; 

    n_pipes = 5;
	numero = 17;
    
	printf("Seu numero é: %d\n", numero);
	printf("Acrescimo: %d\n\n", n_pipes);
    id = 0;
    while (id < n_pipes) 
    {
        if (pipe(fd[id]) < 0) 
        {
            j = 0;
            while (j < id)
            {
                close(fd[j][0]);
                close(fd[j][1]);
                j++;
            }
            exit (1);
        }
        id++;
    }
    id = 0;
    while (id < n_pipes + 1)
    {
        pid[id] = fork();
        if(pid[id] < 0) 
            return 2;   		
    	if(pid[id] == 0) 
    	{
    	    int response_local;
    	    //Pipes ::::::::::::::::::::::::::::::::::::::::
    	    j = 0;
    	    while (j < n_pipes) //write
        	{
        	    if (id != n_pipes && j != id) //jump id
        	        close(fd[j][1]);
        	    j++;				
        	}			
    	    j = 0;    	    
    	    while (j < n_pipes) //read
    	    {
    	        if (id != 0 && j != id - 1)  //jump id - 1
    	            close(fd[j][0]);
    	        j++;				
    	    }
    	    //Msgs ::::::::::::::::::::::::::::::::::::::::
    	    if (id == 0)
    	    {
    	        response_local = numero;
    	        if (write(fd[0][1], &response_local, sizeof(int)) < 0)
    	            return 3;
    	        close(fd[0][1]);
    	    }
    	    else if (id == n_pipes)
    	    {
    	        if (read(fd[n_pipes - 1][0], &response_local, sizeof(int)) < 0)
    	            return 4;
				else
				{
					response_local++;
					printf("I've listening: %d\n", response_local);
				}
    	        close(fd[n_pipes - 1][0]);	        
    	    }
    	    else
    	    {
    	        if (read(fd[id - 1][0], &response_local, sizeof(response_local)) < 0)
    	            return 5;
				else
				{
					response_local++;
    	        	if (write(fd[id][1], &response_local, sizeof(response_local)) < 0)
    	            	return 6;
				}    	         
    	        close(fd[id - 1][0]);
    	        close(fd[id][1]);
    	    }
    	    return 0;
    	}    	
		id++;
	}
	id = 0;
	while (id < n_pipes + 1)
	{
		waitpid(pid[id], NULL, 0);
		id++;
	}    	    
    return 0;
	*/

