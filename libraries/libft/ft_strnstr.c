/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:54:49 by mfrasson          #+#    #+#             */
/*   Updated: 2021/02/21 17:57:07 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *to_find, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!to_find[i])
		return ((char *)src);
	while (i < size && src[i])
	{
		j = 0;
		while (i + j < size && src[i + j] == to_find[j])
		{
			if (!to_find[j + 1])
				return ((char *)&src[i]);
			j++;
		}
		i++;
	}
	return (0);
}
