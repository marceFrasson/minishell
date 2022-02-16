/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:04:46 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/10 15:27:22 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse_command_block(char **command_block)
{
// 	if (command_block[0][0] == '$')
// 		command_block[0] = expanding_variable(command_block[0]);
	// if (!ft_strcmp(command_block[0], "echo"))
	// 	command_echo(command_block);
	// else if (!ft_strcmp(command_block[0], "cd"))
	// 	command_cd(command_block);
	// else if (!ft_strcmp(command_block[0], "pwd"))
	// 	command_pwd();
	if (!ft_strcmp(command_block[0], "export"))
		command_export(command_block);
	// else if (!ft_strcmp(command_block[0], "unset"))
	// 	command_unset();
	else if (!ft_strcmp(command_block[0], "env"))
	 	command_env();
	// else if (!ft_strcmp(command_block[0], "exit"))
	// 	command_exit();
	// else if (ft_strchr(command_block[0], '='))
	// 	add_variable(command_block[0]);
	/*else
		error_message?*/
}

// static void	create_fds(char **command_block, int *fdin, int *fdout)
// {
// 	if (!ft_strcmp(command_block[0], ">"))
// 		open_fd(command_block[1], O_WRONLY | O_CREAT | O_TRUNC, 1, fdout);
// 	else if (!ft_strcmp(command_block[0], "<"))
// 		open_fd(command_block[1], O_RDONLY | O_CREAT, 0, fdin);
// 	else if (!ft_strcmp(command_block[0], ">>"))
// 		open_fd(command_block[1], O_WRONLY | O_CREAT | O_APPEND, 1, fdout);
// 	else
// 		open_heredoc(command_block[1], fdin);
// }

// char    **separate_redirects(char **command_block)
// {
//     char **new_command_block;
//     t_command redirect;
//     int i;
//     int j;

//     i = -1;
//     j = 0;
//     while (command_block[++i])
//     {
//         if (is_redirect(command_block[i]))
//         {
//             redirect->command_block[0] = command_block[i];
//             redirect->command_block[1] = command_block[i + 1];
//         }
//     }
//     i = -1;
//     while (command_block[++i])
//     {
//         if (i != keep_out[0] || i != keep_out[1])
//             new_command_block[j] = command_block[i];
//     }
//     free(command_block);
//     return (new_command_block);
// }

// ___________________________________________________________________________________________________________________


/*

	separar os blocos de comandos separados por pipes em uma lista linkada
	contar cada bloco de comandos da lista e contar quantas palavras tem alem do redirect e sua palavra a direita
	criar um array com o numero de palavras
	copiar pra este array as palavras que nao o redirect e sua palavra a direita
		cria um array com a copia das palavras, apaga o array original e depois aponta pra copia
	executar o comando e passar seus argumentos
	redirecionar


	cria um fd
	cria um pipefd
	fd[0] = pipefd[0]
	pipe(fd)
	fd[1] = pipefd[1]
	redirect fds
	exec comands(fd[0], fd[1])
	close fd[0]
	close fd[1]

	
	getpath
	getenvp(g_global.env_variable, g_global.path)
	execv(char *command, char **command_block, envp)


	exec_buitins
	exec_non_builtins
	
	*/