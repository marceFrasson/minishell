/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:11:54 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/05 00:22:26 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_base_loop(char *base, int i)
{
	char	*base_c;
	int		j;

	base_c = malloc((ft_strlen(base) + 1) * sizeof(char));
	if (!(base_c))
		return (0);
	i = 0;
	*(base_c + i) = '\0';
	while (*(base + i) != '\0')
	{
		j = 0;
		while (*(base_c + j++) != '\0')
		{
			if (*(base + i) == *(base_c + j - 1))
			{
				free(base_c);
				return (0);
			}
		}
		*(base_c + j) = *(base + i);
		*(base_c + j + 1) = '\0';
		i++;
	}
	free(base_c);
	return (1);
}

int	ft_check_base(char *base)
{
	int	i;

	i = 0;
	if (!(base) || ft_strlen(base) == 1)
		return (0);
	while (*(base + i++) != '\0')
		if (*(base + i - 1) || *(base + i - 1) == '+')
			return (0);
	return (check_base_loop(base, i));
}
