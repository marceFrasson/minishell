/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:25:27 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/13 22:13:52 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_splitlen(char **str)
{
	int	i;

	i = 0;
	if (!(str))
		return (i);
	while (*(str + i) != NULL)
		i++;
	return (i);
}

void free_command_list(t_command **command)
{
    t_command *temp1;
    t_command *temp2;

    if (!command)
        return;
    temp1 = *command;
    while (temp1)
    {
        ft_free_split(temp1->command_block);
        temp1 = temp1->next;
    }
    temp1 = *command;
    while (temp1)
    {
        temp2 = temp1->next;
        free(temp1);
        temp1 = temp2;
    }
    *command = NULL;
}

static void	copylen(char *scpy, const char *s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		scpy[i] = s[i];
		i++;
	}
}

int		ft_strjoin_handled(char **s1, char const *s2)
{
	//adiciona s2 ao final de s1
	size_t	len;
	size_t	k;
	char	*s;

	if (!*s1 || !s2)
		return 1;
	len = ft_strlen(*s1) + ft_strlen(s2) + 1;
	if (!(s = (char*)malloc(len * sizeof(char))))
		return 1;
	copylen(s, *s1);
	k = ft_strlen(*s1);
	copylen(&s[k], s2);
	k = k + ft_strlen(s2);
	s[k] = '\0';
	free(*s1); //desprezo s1 antiga
	*s1 = s;
	return 0;
}
