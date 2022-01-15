/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 11:40:10 by itaureli          #+#    #+#             */
/*   Updated: 2022/01/15 11:40:47 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int count_envp(char *envp[])
{
	int i;

	i = 0;
	while(envp[i])
		i++;
	return (i);
}

void    parse_envp(char *envp[])
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    g_global.count = count_envp(envp);
    g_global.envp_variable = malloc(sizeof(char *) * (g_global.count + 30));
    g_global.envp_path = malloc(sizeof(char *) * (g_global.count + 30));
    while(j < g_global.count)
    {
        if(envp[j][i] == '=')
        {
            split_envp(envp, j, i);
            j++;
            i = 0;
        }
        i++;
    }
}

void    split_envp(char *envp[], int j, int i)
{
	char    *first_part;
	char    *second_part;

	first_part = malloc(sizeof(char *) * i + 1);
	second_part = malloc(sizeof(char *) * ((ft_strlen(envp[j]) + 1) - i));

	g_global.envp_variable[j] = ft_substr(envp[j], 0, i);
	g_global.envp_path[j] = ft_substr(envp[j], i + 1, ft_strlen(envp[j]) - 1);

	free(first_part);
	free(second_part);
}

