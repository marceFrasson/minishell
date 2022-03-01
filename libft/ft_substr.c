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

char	*ft_substr(char const *string, unsigned int start, size_t len)
{
	char	*temp;

	if (!(string))
		return (NULL);
	if (len > (size_t)ft_strlen(string))
		len = ft_strlen(string);
	temp = malloc((len + 1) * sizeof(char));
	if (!(temp))
		return (NULL);
	if (len == 0 || start >= (unsigned int)ft_strlen(string))
	{
		*temp = '\0';
		return (temp);
	}
	ft_strlcpy(temp, (const char *)(string + start), len + 1);
	return (temp);
}
