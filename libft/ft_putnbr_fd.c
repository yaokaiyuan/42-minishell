/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradosla <aradosla@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:02:08 by aradosla          #+#    #+#             */
/*   Updated: 2024/02/28 18:18:05 by aradosla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int number, int fd)
{
	char	tmp;

	if (number < 10 && number > -10)
	{
		if (number < 0)
		{
			write(fd, "-", 1);
			number *= -1;
		}
		tmp = number + '0';
		write(fd, &tmp, 1);
	}
	else
	{
		ft_putnbr_fd(number / 10, fd);
		tmp = (number % 10) * (number > 0)
			+ (number % 10) * (number < 0) * (-1) + '0';
		write(fd, &tmp, 1);
	}
}
