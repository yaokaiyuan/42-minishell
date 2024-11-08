/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 07:59:51 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/11/08 15:16:23 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	check_quote(const char *input)
{
	int	in_single_quote;
	int	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	while (*input)
	{
		if (*input == '\'')
			in_single_quote++;
		else if (*input == '\"')
			in_double_quote++;
		input++;
	}
	return (in_single_quote % 2 != 0 || in_double_quote % 2 != 0);
}

static char	*strip_all_quotes(const char *token)
{
	size_t	len;
	size_t	new_len;
	char	*stripped;
	size_t	i;
	size_t	j;

	len = strlen(token);
	new_len = 0;
	i = 0;
	while (i < len)
	{
		if (token[i] != '\'' && token[i] != '\"')
			new_len++;
		i++;
	}
	stripped = malloc(new_len + 1);
	if (!stripped)
		return (NULL);
	j = 0;
	for (i = 0; i < len; i++)
	{
		if (token[i] != '\'' && token[i] != '\"')
			stripped[j++] = token[i];
	}
	stripped[j] = '\0';
	return (stripped);
}

char	*strip_quotes(char *token)
{
	size_t	len;

	len = strlen(token);
	if ((token[0] == '\'' && token[len - 1] == '\'')
		|| (token[0] == '"' && token[len - 1] == '"'))
	{
		token[len - 1] = '\0';
		token++;
	}
	else
		token = strip_all_quotes(token);
	return (token);
}

char	*process_double_quote(const char *input)
{
	int			result_length;
	char		*result;
	char		*ptr;
	const char	*input_ptr;
	int			in_double_quote;

	result_length = get_expanded_length(input);
	result = malloc(result_length + 1);
	if (!result)
		return (NULL);
	ptr = result;
	input_ptr = input;
	in_double_quote = 0;
	while (*input_ptr)
	{
		ptr = handle_double_quote(&input_ptr, ptr, &in_double_quote);
		ptr = handle_dollar(&input_ptr, ptr, in_double_quote);
		if (*input_ptr != '\"' && *input_ptr != '$')
			*ptr++ = *input_ptr++;
	}
	*ptr = '\0';
	return (result);
}
