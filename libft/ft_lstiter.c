/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:10:18 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/05 00:10:21 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;
	t_list	*temp2;

	if (!(lst))
		return ;
	temp = lst;
	while (temp)
	{
		temp2 = temp->next;
		f(temp->vol);
		temp = temp2;
	}
}
