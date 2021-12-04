/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:54:33 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/09 13:39:31 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*store;
	int		i;

	i = ft_strlen(str);
	store = (char *)str;
	while (i >= 0)
	{
		if (store[i] == (unsigned char)c)
			return (&store[i]);
		i--;
	}
	return (NULL);
}
