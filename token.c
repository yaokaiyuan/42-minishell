/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:20:15 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/11/05 19:56:29 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char* ft_strtok(char* str, const char* delim) {
    static char* current_position = NULL;
    char* token;
    int in_single_quote = 0;
    int in_double_quote = 0;

    if (str != NULL) {
        current_position = str;  // Set the current parsing position
    }

    // If the current string has reached the end, return NULL
    if (current_position == NULL || *current_position == '\0') {
        return NULL;
    }

    // Skip leading delimiters
    while (*current_position && strchr(delim, *current_position) && !in_single_quote && !in_double_quote) {
        current_position++;
    }

    // If reached the end of the string, return NULL
    if (*current_position == '\0') {
        return NULL;
    }

    // Find the start position of the token
    token = current_position;

    // Handle quotes and parse the token
    while (*current_position) {
        if (*current_position == '\'') {
            in_single_quote = !in_single_quote;  // Toggle single quote state
            current_position++; // Move past the quote
            continue; // Skip the quote
        } else if (*current_position == '\"') {
            in_double_quote = !in_double_quote;  // Toggle double quote state
            current_position++; // Move past the quote
            continue; // Skip the quote
        }

        // If we are not in quotes and we hit a delimiter, break
        if (!in_single_quote && !in_double_quote && strchr(delim, *current_position)) {
            break;
        }

        current_position++;
    }

    // Null-terminate the token
    if (*current_position) {
        *current_position++ = '\0';  // End the current token and move to the next character
    }

    // Return the token without quotes
    return token;  
}
