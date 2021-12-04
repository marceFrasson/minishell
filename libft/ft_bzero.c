/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:58:24 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/09 13:48:13 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t size)
{
	unsigned char		*s;
	unsigned long int	i;

	i = 0;
	s = str;
	while (i < size)
	{
		s[i] = '\0';
		i++;
	}
}
