#include "shell.h"

int	main(int argc, char **argv, char **envp)
{
	t_program	*program;
	char		*input_cpy;

	(void)argc;
	(void)argv;
	program = init_program(envp);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sigint_handler);
		program->input = readline("minishell> ");
		if (!program->input)
			break ;
		if (is_heredoc(program->input))
		{
            input_cpy = handle_heredoc(program->input);
			if (!input_cpy)
				break ;
            free(program->input);
			program->input = input_cpy;
		}
		signal(SIGQUIT, handle_sigquit);
		signal(SIGINT, handle_sigint_blocking);
		input_cpy = ft_strdup(program->input);
		if (!input_cpy)
			exit(EXIT_FAILURE);
		parse_commands(program);
		if (!program->commands)
		{
			add_history(input_cpy);
			free(input_cpy);
            if (program->tokens)
                free(program->tokens);
			continue ;
		}
		execute_pipeline(&program);
		add_history(input_cpy);
        if (input_cpy)
            free(input_cpy);
		if (program->tokens)
            free(program->tokens);
		free_commands(program->commands);
		program->commands = NULL;
	}
	free_program(program);
	return (0);
}
