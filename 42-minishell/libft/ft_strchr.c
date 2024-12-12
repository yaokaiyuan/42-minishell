/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradosla <aradosla@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:41:15 by aradosla          #+#    #+#             */
/*   Updated: 2024/02/15 13:12:06 by aradosla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;
	int		i;

	ch = (char) c;
	i = 0;
	while (s[i])
	{
		if (ch == s[i])
			return ((char *)(s + i));
		i++;
	}
	if (ch == s[i])
		return ((char *)(s + i));
	return (NULL);
}
