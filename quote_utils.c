/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 07:59:51 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/12/04 19:19:32 by ykai-yua         ###   ########.fr       */
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

static char	*handle_single_quote(const char **input_ptr, char *ptr)
{
	if (**input_ptr == '\'')
	{
		*ptr++ = **input_ptr;
		(*input_ptr)++;
		while (**input_ptr && **input_ptr != '\'')
			*ptr++ = **input_ptr++;
		if (**input_ptr == '\'')
		{
			*ptr++ = **input_ptr;
			(*input_ptr)++;
		}
	}
	else
		*ptr++ = **input_ptr++;
	return (ptr);
}

static char	*handle_double_quotes(t_program *program, const char **input_ptr,
			char *ptr, int *in_double_quote)
{
	if (**input_ptr == '\"')
	{
		*ptr++ = **input_ptr;
		(*input_ptr)++;
		*in_double_quote = !(*in_double_quote);
	}
	if (**input_ptr == '$' && in_double_quote)
	{
		(*input_ptr)++;
		if (**input_ptr && (isalnum(**input_ptr) || **input_ptr == '_'))
			ptr = handle_dollar_sign(program, input_ptr, ptr);
		else
			*ptr++ = '$';
	}
	return (ptr);
}

char	*process_double_quote(t_program *program)
{
	int			result_length;
	char		*result;
	char		*ptr;
	const char	*input_ptr;
	int			in_double_quote;

	result_length = get_expanded_length(program->input);
	result = malloc(result_length + 1);
	if (!result)
		return (NULL);
	ptr = result;
	input_ptr = program->input;
	in_double_quote = 0;
	while (*input_ptr)
	{
		if (*input_ptr == '\'')
			ptr = handle_single_quote(&input_ptr, ptr);
		else if (*input_ptr == '\"')
			ptr = handle_double_quotes(program, &input_ptr,
					ptr, &in_double_quote);
		else
			*ptr++ = *input_ptr++;
	}
	*ptr = '\0';
	return (result);
}
