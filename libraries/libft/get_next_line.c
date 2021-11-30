/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 14:34:58 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/09 13:58:09 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*add_line(char *statik, char **line)
{
	char	*temp;
	size_t	i;

	temp = NULL;
	i = 0;
	while (*(statik + i) != '\n' && *(statik + i) != '\0')
		i++;
	if ((statik)[i] == '\n')
	{
		*line = ft_substr(statik, 0, i);
		temp = ft_strdup(&((statik)[i + 1]));
		free(statik);
	}
	else
	{
		*line = ft_strdup(statik);
		free(statik);
	}
	return (temp);
}

static int	loop(int fd, char *buffer, char **statik, int *n)
{
	char	*temp;

	while (*n > 0)
	{
		*n = read(fd, buffer, 200);
		if (*n < 0)
		{
			free(buffer);
			return (0);
		}
		buffer[*n] = '\0';
		if (*statik == NULL)
			*statik = ft_strdup(buffer);
		else
		{
			temp = ft_strjoin(*statik, buffer);
			free(*statik);
			*statik = temp;
		}
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char		*statik;
	char			*buffer;
	int				n;

	n = 1;
	if (line == NULL || fd < 0 || fd > RLIMIT_NOFILE)
		return (-1);
	buffer = (char *)malloc((200 + 1) * sizeof(char));
	if (!buffer)
		return (-1);
	if (!(loop(fd, buffer, &statik, &n)))
		return (-1);
	statik = add_line(statik, line);
	if (!statik && n == 0)
		return (0);
	return (1);
}
