/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separete_per_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:19:18 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/07 21:43:48 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    separate_per_pipes(char **tokens, t_command **command_list)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (tokens[i])
    {
        if (tokens[i][0] == '|')
        {
            ft_command_add_next(command_list, create_new_node(tokens, j, i));
            j = i + 1;
        }
        i++;
    }
    ft_command_add_next(command_list, create_new_node(tokens, j, i));
}