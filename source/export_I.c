/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_I.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 19:54:27 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/17 15:02:02 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**reassemble_envp(void)
{
	char	**reassembled_envp;
	int		i;

	i = -1;
	reassembled_envp = malloc(sizeof(char *) * g_global.count_env + 1);
	while (g_global.env_variable[++i])
	{
		reassembled_envp[i] = ft_strdup(g_global.env_variable[i]);
		reassembled_envp[i] = ft_strjoin(reassembled_envp[i], "=\"");
		reassembled_envp[i] = ft_strjoin(reassembled_envp[i],
				g_global.env_path[i]);
		reassembled_envp[i] = ft_strjoin(reassembled_envp[i], "\"");
	}
	return (reassembled_envp);
}

static void	sort_envp(char **reassembled_envp)
{
	char	*temp;
	int		i;

	i = -1;
	while (reassembled_envp[++i])
	{
		if (i < g_global.count_env - 1
			&& ft_strcmp(reassembled_envp[i], reassembled_envp[i + 1]) > 0)
		{
			temp = reassembled_envp[i];
			reassembled_envp[i] = reassembled_envp[i + 1];
			reassembled_envp[i + 1] = temp;
			i = -1;
		}
	}
}

static void	print_declare_x(char **reassembled_envp)
{
	int	i;

	i = -1;
	while (reassembled_envp[++i] && i < g_global.count_env - 1)
	{
		ft_putstr_fd("declare -x ", STDOUT);
		ft_putendl_fd(reassembled_envp[i], STDOUT);
	}
}

static void	print_envp_in_alphabetical_order(void)
{
	char	**reassembled_envp;

	reassembled_envp = reassemble_envp();
	sort_envp(reassembled_envp);
	print_declare_x(reassembled_envp);
}

void	command_export(char **tokens)
{
	int	i;
	int	index;

	i = 0;
	index = -1;
	if (!tokens[1])
		print_envp_in_alphabetical_order();
	if (validate_tokens(tokens))
	{
		while (tokens[++i])
		{
			index = does_token_match_local_variable(tokens[i]);
			if (index != DONT_MATCH)
				add_to_env_variable(index);
		}
	}
}
