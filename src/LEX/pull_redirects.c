/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pull_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 20:31:09 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/10/21 20:27:02 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define DIFF_REDIR	"minishell: syntax error near unexpected token `%s'\n"
#define BL_IN_REDIR	"minishell: syntax error near unexpected token `newline'\n"

void	malloc_file(t_data *data, int string_level, int k, int bytes);
int	count_redirects(char *str);
static int	save_file(char *cmd, char **file);

void	find_redirects(t_data *data, int id)
{
	int		j;
	int		k;
	int		init;

	j = -1;
	k = 0;
	while (data->cmds_piped[id][++j])
	{
		if (!ft_strchr("><", data->cmds_piped[id][j]))
			continue ;
		init = j;
		if (data->cmds_piped[id][j] == '>')
			data->file_mode[id][k] = GREAT;
		else if (data->cmds_piped[id][j] == '<')
			data->file_mode[id][k] = LESS;
		if (data->cmds_piped[id][j] == data->cmds_piped[id][j + 1])
			data->file_mode[id][k] *= 2;
		j += 1 + (!(data->file_mode[id][k] % 2));
		j += save_file(data->cmds_piped[id] + j, &data->file[id][k]);
		ft_strcut(&data->cmds_piped[id], init, j);
		j = init - 1;
		if (!data->file[id][k] || !data->cmds_piped[id])
			exit_minishell(data, FAILURE);
		k++;
	}
}

static int	save_file(char *cmd, char **file)
{
	int		end;
	int		init;

	end = 0;
	while (cmd[end] == ' ' && cmd[end])
		end++;
	init = end;
	while (!ft_strchr(" ><", cmd[end]) && cmd[end])
		end++;
	if (cmd[end])
		end--;
	*file = ft_substr(cmd, init, end);
	if (cmd[end])
		end++;
	return (end);
}

int	multiple_redirects_error(char *s, int *i)
{
	int		j;
	char	*str_err;

	j = *i;
	if (s[j] == s[j + 1])
	{
		(*i)++;
		j++;
	}
	(*i)++;
	if (s[*i] == '>' || s[*i] == '<')
	{
		while (((s[*i] != s[j] && s[*i] != '\0')
				&& (s[*i] == '>' || s[*i] == '<')) && *i - j < 3)
			(*i)++;
		if (s[j] == '<')
			str_err = ft_substr(s, j + 1, *i - j - 1);
		else
			str_err = ft_substr(s, j + 1, *i - j);
		ft_printf(STDERR, DIFF_REDIR, str_err);
		free(str_err);
		return (1);
	}
	return (0);
}

int	count_redirects(char *s)
{
	int		i;
	int		redirects_nbr;

	redirects_nbr = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] != '>' && s[i] != '<')
			continue ;
		if (multiple_redirects_error(s, &i))
			return (-1);
		else if (!s[i])
		{
			ft_printf(STDERR, BL_IN_REDIR);
			return (-1);
		}
		redirects_nbr++;
	}
	return (redirects_nbr);
}

void	malloc_file(t_data *data, int string_level, int id, int bytes)
{
	if (!string_level)
	{
		data->file = (char ***)ft_calloc(sizeof(char **), bytes);
		data->file_mode = (char **)ft_calloc(sizeof(char *), bytes);
		if (!data->file || !data->file_mode)
			exit_minishell(data, FAILURE);
	}
	else
	{
		data->file[id] = (char **)ft_calloc(sizeof(char *), bytes);
		data->file_mode[id] = (char *)ft_calloc(sizeof(char), bytes);
		if (!data->file[id] || !data->file_mode[id])
			exit_minishell(data, FAILURE);
	}
}
