/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradosla <aradosla@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:16:43 by aradosla          #+#    #+#             */
/*   Updated: 2024/02/20 13:21:35 by aradosla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, int start, size_t len)
{
	char		*res;
	size_t		finish;
	int			slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (start < 0)
		start = slen + start;
	if (start < 0)
		start = 0;
	finish = slen - start;
	if (finish > len)
		finish = len;
	res = malloc(finish + 1);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, (char *)(s + start), finish + 1);
	return (res);
}
