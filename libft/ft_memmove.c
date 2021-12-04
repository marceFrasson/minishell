/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:31:10 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/09 13:37:04 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t size)
{
	unsigned char	*dst1;
	unsigned char	*src1;
	size_t			i;

	dst1 = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	i = size;
	if (dst == src)
		return (dst);
	if (dst1 > src1)
	{
		while (i > 0)
		{
			dst1[i - 1] = src1[i - 1];
			i--;
		}
	}
	else
		ft_memcpy(dst, src, size);
	return (dst1);
}
