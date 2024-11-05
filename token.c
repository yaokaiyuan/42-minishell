/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:20:15 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/11/05 18:45:51 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char* ft_strtok(char* str, const char* delim) {
    static char* current_position = NULL;
    char* token;
    int in_single_quote = 0;
    int in_double_quote = 0;

    if (str != NULL) {
        current_position = str;  // 设置当前解析的位置
    }

    // 如果当前字符串已到达结尾，则返回NULL
    if (current_position == NULL || *current_position == '\0') {
        return NULL;
    }

    // 跳过前导分隔符
    while (*current_position && strchr(delim, *current_position) && !in_single_quote && !in_double_quote) {
        current_position++;
    }

    // 如果到达了字符串结尾，则返回NULL
    if (*current_position == '\0') {
        return NULL;
    }

    // 找到token的开始位置
    token = current_position;

    // 解析token，直到遇到分隔符或结束引号
    while (*current_position && (in_single_quote || in_double_quote || !strchr(delim, *current_position))) {
        if (*current_position == '\'') {
            in_single_quote = !in_single_quote;  // 切换单引号状态
        } else if (*current_position == '\"') {
            in_double_quote = !in_double_quote;  // 切换双引号状态
        }
        current_position++;
    }

    // 将当前的位置设置为结束符，以便后续调用返回token
    if (*current_position) {
        *current_position++ = '\0';  // 结束当前token，并移动到下一个字符
    }

    return token;  // 返回token
}
