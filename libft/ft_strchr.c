/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:54:18 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/09 13:38:19 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*str1;
	char	c1;
	int		i;

	str1 = (char *)str;
	c1 = (char)c;
	i = 0;
	while (str1[i])
	{
		if (str1[i] == c)
			return (&str1[i]);
		i++;
	}
	if (!c)
		return (&str1[i]);
	return (0);
}
