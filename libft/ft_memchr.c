/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradosla <aradosla@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:31:35 by aradosla          #+#    #+#             */
/*   Updated: 2024/02/15 13:44:24 by aradosla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	ch;
	unsigned char	*str;
	size_t			i;

	ch = (unsigned char) c;
	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ch == str[i])
			return ((void *)(str + i));
		i++;
	}
	return (NULL);
}
