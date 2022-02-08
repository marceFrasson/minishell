/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VII.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:20:09 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/07 21:44:10 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *create_prompt(void)
{
	char	buff[4096];
	char	*prompt_green;
	char	*prompt_reset;
	char	*prompt_full;

	getcwd(buff, sizeof(buff));
	prompt_green = ft_strjoin("\001\033[1;32m\002", buff);
	prompt_reset = ft_strjoin("\001\033[0;0m\002", "$ ");
	prompt_full = ft_strjoin(prompt_green, prompt_reset);
	free(prompt_green);
	free(prompt_reset);
	return (prompt_full);
}

char *read_line(void)
{
	char    *line_read;
	char    *prompt;

	line_read = (char *)NULL;
	prompt = create_prompt();
	line_read = readline(prompt);

	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}
