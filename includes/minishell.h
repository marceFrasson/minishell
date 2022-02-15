/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:04:35 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/15 00:47:37 by ebresser         ###   ########.fr       */
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

#define SUCCESS 0
#define FAILURE 1

#define NOT_ENV 0
#define IS_ENV  1

#define REGULAR   0
#define DECLARE_X 1

#define DONT_MATCH  -1

#define	EXIT 1
#define CD 2

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
	char		*last_input; //guarda ultimo comando p n repetir no hist
	char		**cmd_path;
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

void        print_tokens(char **tokens);
void        print_envp(void);
void        print_command_list(t_command *command);

void        command_echo(char **args, int fdout);
void	    command_env(int ind, int fdout);
void        split_envp(char *envp[], int j, int i);
int         count_envp(char *envp[]);
void        parse_envp(char *envp[]);

void        free_variables(void);
void	    command_exit(char **args);

void        command_export(char **tokens);

void        ft_command_add_next(t_command ** command, t_command *new);
t_command   *create_new_node(char **tokens, int start, int end);

//minishell.c
char        **split_line(char *input_line);
int         take_input(char **input_line);

//operators.c
int	        check_for_operators(char **tokens);
int	        is_operator(char arg);
int	        is_operators(char *arg);

void	    command_pwd(int fdout);

char        *create_prompt(void);
char        *read_line(void);

void        separate_per_pipes(char **tokens, t_command **command_list);
   
//tokenizer.c
int         count_tokens(char *line);
char        **look_for_quotes_and_split(char *line);
char        *look_for_redirections_and_pipe(char *line);
void	    remove_token_quotes(char **tokens);

void	    command_unset(char **args);

//utils.c
int	        ft_splitlen(char **str);
void        free_command_list(t_command **command);
int			ft_strjoin_handled(char **s1, char const *s2);

void	    adding_variables(char **tokens);
void	    add_variable(char *token);
char	    *expanding_variable(char *token);

void	    delete_variable(char *token, int is_env);

//history.c - lilangbr
void		put_on_history(char *buffer);

//init_minishell.c
void		init_g_struct(void);
int			init_cmd_path(void);

//exit_minishell.c
int			free_cmd_path(void);
int			free_env_var(void);
int			free_env_path(void);
int			free_local_var(void);
int			free_local_path(void);

//exec_cmds.c
int exec_commands(t_command *command_list, char *envp[]);
