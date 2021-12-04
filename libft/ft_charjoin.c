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

char	*ft_charjoin(char const *string1, char const c)
{
	char	*string;
	int		i;
	int		end_string1;

	if (!string1 || !c)
		return (NULL);
	string = (char *)malloc(((ft_strlen(string1)) + 2));
	if (string == NULL)
		return (NULL);
	i = 0;
	while (string1[i] != '\0')
	{
		string[i] = string1[i];
		i++;
	}
	end_string1 = i;
	i = 0;
	while (c != '\0')
	{
		string[end_string1 + i] = c;
		i++;
	}
	string[end_string1 + i] = '\0';
	return (string);
}
