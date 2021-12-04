/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:16:57 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/09 13:56:21 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*temp;

	if (!(s))
		return (NULL);
	if (len > (size_t)ft_strlen(s))
		len = ft_strlen(s);
	temp = malloc((len + 1) * sizeof(char));
	if (!(temp))
		return (NULL);
	if (len == 0 || start >= (unsigned int)ft_strlen(s))
	{
		*temp = '\0';
		return (temp);
	}
	ft_strlcpy(temp, (const char *)(s + start), len + 1);
	return (temp);
}
