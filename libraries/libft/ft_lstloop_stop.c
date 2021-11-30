/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstloop_stop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:10:53 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/05 00:21:38 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstloop_stop(t_list **lst)
{
	if (!(*lst))
		return ;
	if (!((*lst)->prev))
		return ;
	((*lst)->prev)->next = NULL;
	(*lst)->prev = NULL;
}
