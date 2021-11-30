/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:58:22 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/09 13:36:46 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t size)
{
	size_t		i;
	char		*dst1;
	const char	*src1;

	i = 0;
	dst1 = (char *)dst;
	src1 = (char *)src;
	if (!dst && !src)
		return (0);
	while (i < size && dst != src)
	{
		dst1[i] = src1[i];
		i++;
	}
	return (dst1);
}
