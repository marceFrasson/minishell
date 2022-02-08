/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:06:05 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/07 22:23:23 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_syntax_error2(char **tokens)
{
	int	i;

	i = ft_splitlen(tokens);
	if (is_operators(tokens[i - 1]))
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `", 2);
		if (is_operators(tokens[i - 1]) == 1)
			ft_putstr_fd("|", 2);
		else
			ft_putstr_fd("newline", 2);
		ft_putendl_fd("'", 2);
		g_global.status = 2;
		return (1);
	}
	return (0);
}

int	check_syntax_error1(char **tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (is_operators(tokens[0]) == 1)
		j++;
	if (!(j))
		while (tokens[++i])
			if (is_operators(tokens[i]) && is_operators(tokens[i - 1]))
				break ;
	if (j || i != ft_splitlen(tokens))
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `", 2);
		if (j)
			ft_putstr_fd(tokens[0], 2);
		else
			ft_putstr_fd(tokens[i], 2);
		ft_putendl_fd("'", 2);
		g_global.status = 2;
		return (1);
	}
	return (0);
}
