/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numdigt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:12:20 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/05 00:23:50 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numdigt(int unsigned base, int n)
{
	unsigned int	cont;
	unsigned int	num;

	if (n < 0)
	{
		num = -n;
		cont = 2;
	}
	else
	{
		num = n;
		cont = 1;
	}
	while (num >= base && cont++)
		num /= base;
	return (cont);
}
