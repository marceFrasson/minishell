/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstloop_start.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:10:43 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/05 00:10:45 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstloop_start(t_list **lst)
{
	t_list	*temp;

	if (!(*lst))
		return ;
	temp = ft_lstlast(*lst);
	(*lst)->prev = temp;
	temp->next = *lst;
}
