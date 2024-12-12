/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradosla <aradosla@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:13:12 by aradosla          #+#    #+#             */
/*   Updated: 2024/02/15 13:25:59 by aradosla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	char	*ans;
	int		i;

	ch = (char) c;
	i = 0;
	ans = NULL;
	while (s[i])
	{
		if (ch == s[i])
			ans = ((char *)(s + i));
		i++;
	}
	if (ch == s[i])
		ans = ((char *)(s + i));
	return (ans);
}
