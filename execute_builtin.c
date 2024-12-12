#include "shell.h"

void	execute_builtin_command(t_command *cmd, t_list *env_list)
{
	char	*exit_status;

	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		builtin_echo(cmd->argv);
	else if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		builtin_cd(cmd->argv, env_list);
	else if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		builtin_pwd();
	else if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		builtin_export(cmd->argv, env_list);
	else if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		builtin_unset(cmd->argv, env_list);
	else if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		builtin_env(env_list);
	else if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		builtin_exit(cmd->argv);
	else if (ft_strncmp(cmd->argv[0], "$?", 3) == 0)
	{
		exit_status = get_env_value(env_list, "?");
		if (exit_status)
			printf("minishell: %s\n", exit_status);
		else
			printf("minishell: $? not found\n");
	}
}

// TODO free and exit on exit
void	execute_builtin_with_redirection(t_command *cmd, t_program **program)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(1);
	saved_stdin = dup(0);
	if (saved_stdout == -1 || saved_stdin == -1)
	{
		perror("Failed to save STDIN or STDOUT");
		exit(EXIT_FAILURE);
	}
	dup2((*program)->in_fd, 0);
	dup2((*program)->out_fd, 1);
	handle_redirection(cmd);
	execute_builtin_command(cmd, (*program)->envp);
	dup2(saved_stdin, 0);
	dup2(saved_stdout, 1);
	close(saved_stdin);
	close(saved_stdout);
}
