/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:11:15 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/05 00:21:49 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *vol)
{
	t_list	*lst;

	lst = (t_list *)malloc(sizeof(t_list));
	if (!(lst))
		return (NULL);
	lst->prev = NULL;
	lst->vol = vol;
	lst->next = NULL;
	return (lst);
}
