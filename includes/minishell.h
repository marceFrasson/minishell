/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:04:35 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/16 17:29:41 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

#define BUFFERSIZE 1024

#define OFF 0
#define ON  1

#define NOT_ENV 0
#define IS_ENV  1

#define REGULAR   0
#define DECLARE_X 1

#define DONT_MATCH  -1

#define STDIN   0
#define STDOUT  1
#define STDER   2

typedef struct s_command
{
    char              **command_block;
    int               word_count;
    struct s_command  *next;
}               t_command;

typedef struct s_global
{
    char        **env_variable;
    char        **env_path;
    char        **local_variable;
    char        **local_path;
    int         count;
    int         count_local;
    int         status;
    t_command   *head;
}              t_global;

t_global         g_global;

int	        search_variable(char *variable);
char 	    change_dir_to_path(char *path);
void	    change_dir_to_oldpwd(void);
void	    change_dir_to_home(void);
void	    command_cd(char **args);

int    	    check_syntax_error2(char **tokens);
int    	    check_syntax_error1(char **tokens);

void    	parse_command_block(char **command_block);

void        print_tokens(char **tokens);
void        print_envp(void);
void        print_command_list(t_command *command);

void        command_echo(char **args, int fdout);
void	    command_env(void);
void        split_envp(char *envp[], int j, int i);
int         count_envp(char *envp[]);
void        parse_envp(char *envp[]);

void        free_variables(void);
void	    command_exit(char **args);

void        command_export(char **tokens);

void        ft_command_add_next(t_command ** command, t_command *new);
t_command   *create_new_node(char **tokens, int start, int end);

char        **split_line(char *input_line);
int         take_input(char **input_line);

int	        check_for_operators_or_quotes(char **tokens);
int	        is_operator(char arg);
int	        is_operators(char *arg);

void	    command_pwd(int fdout);

char        *create_prompt(void);
char        *read_line(void);

void        separate_per_pipes(char **tokens, t_command **command_list);

int         count_tokens(char *line);
char        **look_for_quotes_and_split(char *line);
char        *look_for_redirections_and_pipe(char *line);
void	    remove_token_quotes(char **tokens);

void	    command_unset(char **args);

int	        ft_splitlen(char **str);
void        free_command_list(t_command **command);

void	    adding_variables(char **tokens);
void	    add_variable(char **token);
char	    *expanding_variable(char *token);

void	    delete_variable(char *token, int is_env);
