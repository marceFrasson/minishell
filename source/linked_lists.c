/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VIII.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:21:02 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/07 21:45:23 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_command_add_next(t_command ** command, t_command *new)
{
    t_command    *temp;

    if (!(new))
        return ;
    else if (!(*command))
    {
        *command = new;
        return ;
    }
    temp = *command;
    while (temp->next)
        temp = temp->next;
    temp->next = new;
}

t_command    *create_new_node(char **tokens, int start, int end)
{
    t_command *new_node;
    int count;
    int i;

    i = -1;
    count = end - start;
    new_node = (t_command *)malloc(sizeof(t_command));
    new_node->command_block = malloc(sizeof(char *) * (count + 1));
    new_node->command_block[count] = NULL;
    new_node->word_count = count;
    new_node->next = NULL;
    while (++i < count)
        new_node->command_block[i] = ft_strdup(tokens[start + i]);
    return (new_node);
}
