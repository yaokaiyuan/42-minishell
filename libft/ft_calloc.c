/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradosla <aradosla@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:16:45 by aradosla          #+#    #+#             */
/*   Updated: 2024/02/23 12:06:36 by aradosla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*res;

	res = malloc(size * count);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, size * count);
	return (res);
}
