/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:11:02 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/05 00:11:04 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*c_lst;
	t_list	*temp;

	c_lst = NULL;
	if (!(lst))
		return (c_lst);
	while (lst)
	{
		temp = ft_lstnew(f(lst->vol));
		if (!(temp))
		{
			ft_lstclear(&c_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&c_lst, temp);
		lst = lst->next;
	}
	return (c_lst);
}
