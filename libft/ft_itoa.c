/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradosla <aradosla@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:53:42 by aradosla          #+#    #+#             */
/*   Updated: 2024/02/20 14:10:49 by aradosla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	get_len_sign(int n, int *len, int *sign)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		*sign = -1;
		i++;
	}
	else
		*sign = 1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	*len = i;
}

char	*ft_itoa(int n)
{
	char	*res;
	int		sign;
	int		i;
	int		len;

	if (n == 0)
		return (ft_strdup("0"));
	get_len_sign(n, &len, &sign);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	if (sign == -1)
	{
		res[0] = '-';
		i++;
	}
	while (i < len)
	{
		res[len - (sign > 0) - i] = n % 10 * sign + '0';
		n /= 10;
		i++;
	}
	res[i] = '\0';
	return (res);
}
