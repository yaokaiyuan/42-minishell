/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradosla <aradosla@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:02:55 by aradosla          #+#    #+#             */
/*   Updated: 2024/02/16 13:23:17 by aradosla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	res_size;

	if (!s1 || !s2)
		return (NULL);
	res_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	res = malloc(res_size);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, res_size);
	ft_strlcat(res, s2, res_size);
	return (res);
}
