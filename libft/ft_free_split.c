/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:12:04 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/09 13:48:32 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char **str)
{
	int	i;

	i = 0;
	while (*(str + i++) != NULL)
	{
		free(*(str + i - 1));
		*(str + i - 1) = NULL;
	}
	free(str);
	str = NULL;
}
