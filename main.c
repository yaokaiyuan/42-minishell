#include "shell.h"

void	partly_clear(t_program *program, char *input_cpy)
{
	add_history(input_cpy);
	if (input_cpy)
		free(input_cpy);
	if (program->tokens)
		free(program->tokens);
}

static int	handle_input(t_program *program)
{
	char	*input_cpy;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	program->input = readline("minishell> ");
	if (!program->input)
		return (0);
	if (is_heredoc(program->input))
	{
		input_cpy = handle_heredoc(program->input);
		if (!input_cpy)
			return (0);
		free(program->input);
		program->input = input_cpy;
	}
	return (1);
}

static int	process_commands(t_program *program)
{
	char	*input_cpy;

	signal(SIGQUIT, handle_sigquit);
	signal(SIGINT, handle_sigint_blocking);
	input_cpy = ft_strdup(program->input);
	if (!input_cpy)
		exit(EXIT_FAILURE);
	parse_commands(program);
	if (!program->commands)
	{
		partly_clear(program, input_cpy);
		return (1);
	}
	execute_pipeline(&program);
	partly_clear(program, input_cpy);
	free_commands(program->commands);
	program->commands = NULL;
	return (1);
}

static void	run_shell(t_program *program)
{
	while (1)
	{
		if (!handle_input(program))
			break ;
		if (!process_commands(program))
			continue ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_program	*program;

	(void)argc;
	(void)argv;
	program = init_program(envp);
	run_shell(program);
	free_program(program);
	return (0);
}
