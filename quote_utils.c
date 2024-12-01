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

char *strip_quotes(char *token)
{
    if (token == NULL) // 检查 token 是否为 NULL
        return NULL;

    size_t len = strlen(token);
    if (len == 0) // 检查空字符串
        return token; // 直接返回原始字符串

    size_t end = 0;
    int in_quote = 0; // 用于跟踪是否在引号内
    char quote_char = 0; // 用于存储当前引号类型

    // 创建一个临时结果字符串
    char *result = malloc(len + 1); // 最坏情况下，长度等于原始字符串长度
    if (!result)
        return NULL; // 如果分配失败，返回 NULL

    size_t j = 0; // 用于跟踪 result 的写入位置

    while (end < len)
    {
        if (!in_quote && (token[end] == '\'' || token[end] == '\"'))
        {
            // 找到开头引号
            in_quote = 1;
            quote_char = token[end]; // 记录引号类型
            end++; // 跳过当前引号
            continue;
        }

        if (in_quote)
        {
            // 在引号内，检查是否遇到成对的引号
            if (token[end] == quote_char)
            {
                in_quote = 0; // 退出引号状态
                end++; // 跳过当前引号
                continue;
            }
        }

        // 复制非引号字符到 result
        result[j++] = token[end++];
    }

    result[j] = '\0'; // 确保 result 是一个以空字符结尾的字符串
	if (in_quote)
    {
        free(result); // 释放临时结果
        return strdup("minishell: unmatched quotes"); // 返回错误信息
    }
    // 将结果复制回原始 token（覆盖原始内容）
    strncpy(token, result, j + 1); // 包括空字符
    free(result); // 释放临时结果

    return token; // 返回原始 token（现在是处理后的字符串）
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
