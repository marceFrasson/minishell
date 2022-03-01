/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 23:35:33 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/09 13:59:26 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod(const char *str)
{
	int		i;
	double	j;
	double	num[3];

	i = 0;
	j = 10;
	num[0] = 0;
	num[1] = 0;
	num[2] = 1;
	while (str[i + 1] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			num[2] *= -1;
	while (ft_isdigit(str[i]))
		num[0] = (num[0] * 10) + (str[i++] - '0');
	if (str[i] == '.')
	{
		while (ft_isdigit(str[++i]))
		{
			num[1] += (str[i] - '0') / j;
			j *= 10;
		}
	}
	return ((num[0] + num[1]) * num[2]);
}
