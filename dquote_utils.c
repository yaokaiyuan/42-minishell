/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:56:26 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/11/08 11:10:24 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	get_env_var_length(const char **input_ptr)
{
	char	var_name[256];
	int		i;
	char	*env_value;

	i = 0;
	while (**input_ptr && (isalnum(**input_ptr) || **input_ptr == '_'))
	{
		var_name[i++] = **input_ptr;
		(*input_ptr)++;
	}
	var_name[i] = '\0';
	env_value = getenv(var_name);
	if (env_value)
		return (ft_strlen(env_value));
	return (0);
}

int	get_expanded_length(const char *input)
{
	int		length;
	int		in_double_quote;

	length = 0;
	in_double_quote = 0;
	while (*input)
	{
		if (*input == '\"')
		{
			in_double_quote = !in_double_quote;
			length++;
			input++;
		}
		else if (*input == '$' && in_double_quote)
		{
			input++;
			length += get_env_var_length(&input);
		}
		else
		{
			length++;
			input++;
		}
	}
	return (length);
}

char	*handle_dollar_sign(const char **input_ptr, char *ptr)
{
	char	var_name[256];
	char	*env_value;
	int		i;

	(*input_ptr)++;
	i = 0;
	while (**input_ptr && (isalnum(**input_ptr) || **input_ptr == '_'))
	{
		var_name[i++] = **input_ptr;
		(*input_ptr)++;
	}
	var_name[i] = '\0';
	env_value = getenv(var_name);
	if (env_value)
	{
		ft_strlcpy(ptr, env_value, ft_strlen(env_value) + 1);
		ptr += ft_strlen(env_value);
	}
	return (ptr);
}

char	*handle_double_quote(const char **input_ptr,
			char *ptr, int *in_double_quote)
{
	if (**input_ptr == '\"')
	{
		*ptr++ = **input_ptr;
		(*input_ptr)++;
		*in_double_quote = !(*in_double_quote);
	}
	return (ptr);
}

char	*handle_dollar(const char **input_ptr,
			char *ptr, int in_double_quote)
{
	if (**input_ptr == '$' && in_double_quote)
		ptr = handle_dollar_sign(input_ptr, ptr);
	return (ptr);
}
