/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradosla <aradosla@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:36:57 by aradosla          #+#    #+#             */
/*   Updated: 2024/02/21 11:21:54 by aradosla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **list, void (*del)(void *))
{
	if (!*list || !del)
		return ;
	if (*list && list)
	{
		ft_lstclear(&(*list)->next, del);
		ft_lstdelone(*list, del);
		*list = NULL;
	}
	return ;
}
