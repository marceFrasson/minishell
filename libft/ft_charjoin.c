/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marce <marce@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 20:32:10 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/13 18:41:30 by marce            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_charjoin(char const *string, char const c)
{
	int		i;
	char	*temp_string;

	temp_string = (char *)NULL;
	if (!string || !c)
		return (NULL);
	temp_string = malloc(sizeof(char *) * ((ft_strlen(string)) + 3));
	if (string == NULL)
		return (NULL);
	i = 0;
	while (string[i] != '\0')
	{
		temp_string[i] = string[i];
		i++;
	}
	temp_string[i++] = c;
	temp_string[i] = '\0';
	return (temp_string);
}
