/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:23:39 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/09 13:59:12 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *str, char const *ref)
{
	size_t	i;
	size_t	size;

	if (!str || !ref)
		return (NULL);
	i = 0;
	while (str[i] && ft_strchr(ref, str[i]))
		i++;
	size = ft_strlen(&str[i]);
	if (size)
		while (str[i + size - 1]
			&& ft_strrchr(ref, str[i + size - 1]))
			size--;
	return (ft_substr(str, i, size));
}
