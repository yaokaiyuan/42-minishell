/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradosla <aradosla@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:00:58 by aradosla          #+#    #+#             */
/*   Updated: 2024/02/21 11:45:40 by aradosla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *list, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*curr;

	if (!list || !f || !del)
		return (NULL);
	res = ft_lstnew(f(list->content));
	if (!res)
		return (NULL);
	list = list->next;
	curr = res;
	while (list)
	{
		curr->next = ft_lstnew(f(list->content));
		if (!curr->next)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		curr = curr->next;
		list = list->next;
	}
	return (res);
}
