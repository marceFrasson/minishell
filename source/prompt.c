/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 12:00:47 by itaureli          #+#    #+#             */
/*   Updated: 2022/01/15 12:00:57 by itaureli         ###   ########.fr       */
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
