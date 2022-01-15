/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:04:46 by mfrasson          #+#    #+#             */
/*   Updated: 2022/01/15 12:06:57 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	//printf("oie aqui eh\n");
	parse_envp(envp);
	loop();
	return (0);
}

// ___________________________________________________________________________________________________________________


/*

	separar os blocos de comandos separados por pipes em uma lista linkada
	contar cada bloco de comandos da lista e contar quantas palavras tem alem do redirect e sua palavra a direita
	criar um array com o numero de palavras
	copiar pra este array as palavras que nao o redirect e sua palavra a direita
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
	getenvp(g_global.envp_variable, g_global.envp_path)
	execv(char *command, char **command_block, envp)


	exec_buitins
	exec_non_builtins

	*/
