/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 07:59:51 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/12/12 18:25:16 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	process_quotes(char *token, size_t len
							, char *result, int *in_quote)
{
	size_t	end;
	size_t	j;
	char	quote_char;

	end = 0;
	j = 0;
	while (end < len)
	{
		if (!*in_quote && (token[end] == '\'' || token[end] == '\"'))
		{
			*in_quote = 1;
			quote_char = token[end];
			end++;
		}
		else if (*in_quote && token[end] == quote_char)
		{
			*in_quote = 0;
			end++;
		}
		else
			result[j++] = token[end++];
	}
	result[j] = '\0';
	ft_strlcpy(token, result, j + 1);
}

char	*strip_quotes(char *token)
{
	size_t	len;
	char	*result;
	int		in_quote;

	in_quote = 0;
	if (token == NULL)
		return (NULL);
	len = ft_strlen(token);
	if (len == 0)
		return (token);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	process_quotes(token, len, result, &in_quote);
	if (in_quote)
	{
		free(result);
		return (ft_strdup("minishell: unmatched quotes"));
	}
	free(result);
	return (token);
}

char	*process_double_quote(t_program *program)
{
	char		*result;
	const char	*input;
	char		*ptr;
	int			in_double_quote;
	int			in_single_quote;

	input = program->input;
	result = malloc(get_expanded_length(program->input) + 1);
	if (!result)
		exit(EXIT_FAILURE);
	ptr = result;
	in_double_quote = 0;
	in_single_quote = 0;
	while (*input)
	{
		if (*input == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (*input == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*input == '$' && !in_single_quote)
		{
			input++;
			ptr = handle_dollar_sign(program, &input, ptr);
			continue ;
		}
		*ptr++ = *input++;
	}
	*ptr = '\0';
	return (result);
}
