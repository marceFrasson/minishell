/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:04:35 by mfrasson          #+#    #+#             */
/*   Updated: 2022/01/14 16:29:15 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

#define BUFFERSIZE 1024

#define OFF 0
#define ON  1

typedef struct s_command
{
    char              **command_block;
    int               word_count;
    struct s_command  *next;
}               t_command;

typedef struct s_global
{
    char        **envp_variable;
    char        **envp_path;
    int         count;
    t_command   *head;
}              t_global;

t_global         g_global;
