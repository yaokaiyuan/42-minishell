#include "shell.h"

t_program	*init_program(char **envp)
{
	t_program	*program;

	program = malloc(sizeof(t_program));
	if (!program)
		exit(EXIT_FAILURE);
	program->input = NULL;
	program->tokens = NULL;
	program->commands = NULL;
	program->envp = init_env_list(envp);
	if (!program->envp)
	{
		free(program);
		exit(EXIT_FAILURE);
	}
	return (program);
}

t_command	*init_command(void)
{
	t_command	*new_cmd;

	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->argv = NULL;
	new_cmd->redirects = NULL;
	new_cmd->append = 0;
	new_cmd->next = NULL;
	new_cmd->flag_error = 0;
	return (new_cmd);
}
