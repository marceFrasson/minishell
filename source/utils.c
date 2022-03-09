/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:25:27 by mfrasson          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/02/23 20:48:21 by ebresser         ###   ########.fr       */
=======
/*   Updated: 2022/03/03 02:01:18 by mfrasson         ###   ########.fr       */
>>>>>>> main
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

void	free_tokens(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i] && i < g_global.token_count - 1)
	{
		free(tokens[i]);
		tokens[i] = NULL;
	}
	free(tokens);
	tokens = NULL;
}

void	free_command(t_command *command)
{
	int i;

	i = -1;
	while (command->command_block[++i] != NULL)
		free(command->command_block[i]);
}

<<<<<<< HEAD
int command_list_len(t_command *command_list)
{
	int			len;
	t_command	*ptr;

	len = 0;
	ptr = command_list;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		len++;
	}
	return len;
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
=======
void	free_command_list(t_command **command)
{
	t_command	*temp;

	if (!*command)
		return ;
	temp = *command;
	if ((*command)->command_block)
		free_command(*command);
	free(*command);
	*command = temp->next;
	if (temp->next)
		free_command_list(command);
}



	// printf("\n1 : %s\n\n", (*(command))->command_block[0]);
	// printf("\n2 : %s\n", (*(command))->command_block[0]);
	// printf("\nbefore free : %i\n\n", (*command)->word_count);
	// printf("\n3 : %p\n", *command);
	// printf("3 : %p\n\n", *command);
	// printf("\nafter  free : %i\n\n", (*command)->word_count);
	// printf("\n4 : %s\n\n", (*(command))->command_block[0]);
	// printf("\ncmnd : %p\ntemp : %p\n\n", *command, temp);
>>>>>>> main
