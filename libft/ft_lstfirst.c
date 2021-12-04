/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfirst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:10:04 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/05 00:21:19 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfirst(t_list *lst)
{
	t_list	*temp;

	if (!(lst))
		return (lst);
	temp = lst;
	while (temp->prev)
		temp = temp->prev;
	return (temp);
}
