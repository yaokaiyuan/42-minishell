/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradosla <aradosla@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:56:13 by aradosla          #+#    #+#             */
/*   Updated: 2024/02/16 14:27:24 by aradosla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res;
	size_t	size;

	size = ft_strlen(s1) + 1;
	res = malloc((int)size);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, size);
	return (res);
}
