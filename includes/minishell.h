/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:04:35 by mfrasson          #+#    #+#             */
/*   Updated: 2022/01/15 12:01:22 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

#define BUFFERSIZE 1024

#define OFF 0
#define ON  1

typedef struct s_command
{
    char              **command_block;
    struct s_command  *next;
}               t_command;

typedef struct s_global
{
    char        **envp_variable;
    char        **envp_path;
    int         count;
    t_command   *first_command;
}              t_global;

t_global	g_global;

int	exec_commands();

// VALIDATORS
char	*look_for_redirections_and_pipe(char *line);
char	**look_for_quotes_and_split(char *line);
int		count_tokens(char *line);
int		is_operator(char arg);
int		check_syntax(char **tokens);

// ENVP
void	split_envp(char *envp[], int j, int i);
void	parse_envp(char *envp[]);
void	split_envp(char *envp[], int j, int i);

// LOOP
void	loop(void);

// PROMPT
char	*create_prompt(void);
# endif
