/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 08:13:05 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/11/08 08:26:38 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_redirection_type	get_redirection_type(char *token)
{
	if (ft_strncmp(token, ">", 1) == 0)
		return (REDIRECT_OUT);
	return (REDIRECT_IN);
}

static t_redirection	*create_redirection(char *token,
					t_redirection_type type)
{
	t_redirection	*new_redirection;

	new_redirection = malloc(sizeof(t_redirection));
	if (!new_redirection)
		exit(EXIT_FAILURE);
	new_redirection->file = ft_strdup(token);
	if (!new_redirection->file)
		exit(EXIT_FAILURE);
	new_redirection->type = type;
	new_redirection->next = NULL;
	return (new_redirection);
}

static void	add_redirection(t_command *current_cmd,
					t_redirection *new_redirection)
{
	t_redirection	*tmp;

	if (!current_cmd->redirects)
		current_cmd->redirects = new_redirection;
	else
	{
		tmp = current_cmd->redirects;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_redirection;
	}
}

void	handle_redirection_token(t_program *program,
		t_command *current_cmd, char *token)
{
	t_redirection_type	type;
	t_redirection		*new_redirection;

	if (!current_cmd)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n",
			STDERR_FILENO);
		return ;
	}
	type = get_redirection_type(token);
	if (ft_strncmp(token, ">>", 2) == 0)
		current_cmd->append = 1;
	program->tokens = ft_strtok(NULL, " ");
	token = strip_quotes(program->tokens);
	if (token)
	{
		new_redirection = create_redirection(token, type);
		add_redirection(current_cmd, new_redirection);
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n",
			STDERR_FILENO);
	}
}
