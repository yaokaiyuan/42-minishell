/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradosla <aradosla@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:36:59 by aradosla          #+#    #+#             */
/*   Updated: 2024/02/28 17:51:11 by aradosla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
				i++;
			res++;
		}
		else
			i++;
	}
	return (res);
}

static int	check_res(char **ret, size_t index)
{
	if (!ret || !ret[index - 1])
	{
		while (index > 0)
		{
			free(ret[--index]);
		}
		free(ret);
		return (1);
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		len;
	int		i;

	res = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!s || !res)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				++s;
			res[i++] = ft_substr(s - len, 0, len);
			if (check_res(res, i))
				return (NULL);
		}
		else
			++s;
	}
	res[i] = NULL;
	return (res);
}
