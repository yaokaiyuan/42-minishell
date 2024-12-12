/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:24:07 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/12/12 18:58:10 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*process_redirections_outside_quotes(char *input)
{
	char	*result;
	int		i = 0;
	int		j = 0;
	int		in_single_quote = 0;
	int		in_double_quote = 0;

	result = malloc(sizeof(char) * (strlen(input) * 3 + 1));
	if (!result)
		exit(EXIT_FAILURE);
	while (input[i])
	{
		if (input[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (input[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if ((input[i] == '<' || input[i] == '>')
			&& !in_single_quote && !in_double_quote)
		{
			if (i > 0 && j > 0 && result[j - 1] != ' ')
				result[j++] = ' ';
			result[j++] = input[i];
			if (input[i + 1] == input[i])
				result[j++] = input[++i];
			if (input[i + 1] && input[i + 1] != ' ')
				result[j++] = ' ';
		}
		else
			result[j++] = input[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
