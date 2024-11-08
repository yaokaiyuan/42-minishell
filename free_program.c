#include "shell.h"

void	free_program(t_program *program)
{
	if (program->input)
		free(program->input);
	if (program->tokens)
		free(program->tokens);
	if (program->commands)
		free_commands(program->commands);
	if (program->envp)
		clean_env_list(program->envp);
	free(program);
}
