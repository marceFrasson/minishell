/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:22:03 by mfrasson          #+#    #+#             */
/*   Updated: 2022/03/01 13:20:36 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_variables(void)
{
	int	i;

	i = -1;
	printf("\n--------\n");
	while (g_global.local_variable[++i])
		printf("%s=%s\n", g_global.local_variable[i], g_global.local_path[i]);
	printf("--------\n\n");
}

void    print_tokens(char **tokens)
{
	int i;
	
	i = -1;
	while (tokens[++i])
		printf("%i: %s\n", i, tokens[i]);
}

void    print_envp(void)
{
	int i = -1;
	while (++i < g_global.count_env)
		printf("var: %s\npath: %s\n", g_global.env_variable[i], g_global.env_path[i]);
}

void    print_command_list(t_command *command_list)
{
    while (command_list)
    {
        printf("\n---cmd---\n");
        print_tokens(command_list->command_block);
        printf("---cmd---\n");
		printf("cmd count = %i\n\n", command_list->word_count);
        command_list = command_list->next;
    }
}
