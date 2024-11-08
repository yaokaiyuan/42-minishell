/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 07:42:19 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/11/08 15:27:16 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	quote_spaces(char **current_position, const char *delim,
						int *in_single_quote, int *in_double_quote)
{
	while (**current_position)
	{
		if (**current_position == '\'' && !(*in_double_quote))
			*in_single_quote = !(*in_single_quote);
		else if (**current_position == '\"' && !(*in_single_quote))
			*in_double_quote = !(*in_double_quote);
		else if (!(*in_single_quote) && !(*in_double_quote)
			&& ft_strchr(delim, **current_position))
			break ;
		(*current_position)++;
	}
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*current_position;
	char		*token;
	int			in_single_quote;
	int			in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	if (str)
		current_position = str;
	if (!current_position || *current_position == '\0')
		return (NULL);
	while (*current_position && ft_strchr(delim, *current_position)
		&& !in_single_quote && !in_double_quote)
		current_position++;
	if (*current_position == '\0')
		return (NULL);
	token = current_position;
	quote_spaces(&current_position, delim, &in_single_quote, &in_double_quote);
	if (*current_position)
		*current_position++ = '\0';
	return (token);
}
