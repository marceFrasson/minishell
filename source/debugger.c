/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:22:03 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/09 15:49:34 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	while (++i < g_global.count)
		printf("var: %s\npath: %s\n", g_global.env_variable[i], g_global.env_path[i]);
}

void    print_command_list(t_command *command)
{
    while (command)
    {
        printf("-----\n");
        print_tokens(command->command_block);
        printf("-----\n");
        command = command->next;
    }
}
