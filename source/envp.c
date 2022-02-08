/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:13:18 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/07 22:25:27 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    split_envp(char *envp[], int j, int i)
{
	g_global.variable[j] = ft_substr(envp[j], 0, i);
	g_global.path[j] = ft_substr(envp[j], i + 1, ft_strlen(envp[j]) - 1);
}

int count_envp(char *envp[])
{
	int i;

	i = 0;
	while (envp[i])
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
    g_global.variable = malloc(sizeof(char *) * (g_global.count + 30));
    g_global.path = malloc(sizeof(char *) * (g_global.count + 30));
    while (j < g_global.count)
    {
        if (envp[j][i] == '=')
        {
            split_envp(envp, j, i);
            j++;
            i = 0;
        }
        i++;
    }
}