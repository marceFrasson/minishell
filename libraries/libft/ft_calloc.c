/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:29:24 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/09 14:00:03 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t str, size_t size)
{
	size_t	s;
	size_t	len;

	s = 0;
	len = str * size;
	s = (size_t)malloc(len);
	if (!s)
		return (NULL);
	ft_bzero((void *)s, len);
	return ((void *)s);
}
