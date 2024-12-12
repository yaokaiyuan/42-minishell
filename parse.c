/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 08:00:32 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/12/12 18:51:46 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	add_argument_to_command(t_command *current_cmd, char *token)
{
	char	**new_argv;
	int		argc;

	if (!current_cmd)
		return ;
	argc = 0;
	while (current_cmd->argv && current_cmd->argv[argc])
		argc++;
	new_argv = ft_realloc(current_cmd->argv, sizeof(char *) * (argc + 2));
	if (!new_argv)
		exit(EXIT_FAILURE);
	new_argv[argc] = ft_strdup(token);
	if (!new_argv[argc])
		exit(EXIT_FAILURE);
	new_argv[argc + 1] = NULL;
	current_cmd->argv = new_argv;
}

static t_command	*init_new_command(t_command **head, t_command **current_cmd)
{
	if (!(*head))
		*head = init_command();
	else
	{
		(*current_cmd)->next = init_command();
		*current_cmd = (*current_cmd)->next;
	}
	return (*current_cmd);
}

static void	process_token(t_command **current_cmd,
		char *token, t_command **head)
{
	if (!(*current_cmd))
	{
		*current_cmd = init_command();
		if (!(*head))
			*head = *current_cmd;
	}
	add_argument_to_command(*current_cmd, token);
}

void	parse_tokens(t_program *program)
{
	t_command	*current_cmd;
	t_command	*head;
	char		*token;

	current_cmd = NULL;
	head = NULL;
	while (program->tokens)
	{
		token = strip_quotes(program->tokens);
		if (ft_strncmp(token, "|", 2) == 0)
			current_cmd = init_new_command(&head, &current_cmd);
		else if (ft_strncmp(token, ">", 2) == 0
			|| ft_strncmp(token, "<", 2) == 0
			|| ft_strncmp(token, ">>", 3) == 0)
			handle_redirection_token(program, current_cmd, token);
		else
			process_token(&current_cmd, token, &head);
		program->tokens = ft_strtok(NULL, " ");
	}
	program->commands = head;
}

void	parse_commands(t_program *program)
{
	char	*processed_input;
	char	*redirections_processed;

	processed_input = process_double_quote(program);
	if (processed_input)
	{
		redirections_processed
			= process_redirections_outside_quotes(processed_input);
		free(processed_input);
		free(program->input);
		program->input = redirections_processed;
	}
	program->tokens = ft_strtok(program->input, " ");
	if (!program->tokens)
		return ;
	parse_tokens(program);
}
