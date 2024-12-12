#include "shell.h"

int	count_commands(t_program *program)
{
	int			i;
	t_command	*current_cmd;

	current_cmd = program->commands;
	i = 0;
	while (current_cmd)
	{
		current_cmd = current_cmd->next;
		i++;
	}
	return (i);
}

void	wait_for_children(int num_commands, t_program **program)
{
	int		status;
	int		exit_code;
	char	*exit_code_str;
	int		i;

	exit_code = 0;
	i = 0;
	while (i < num_commands)
	{
		if (wait(&status) == -1)
		{
			perror("wait");
			continue ;
		}
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_code = 128 + WTERMSIG(status);
		i++;
	}
	exit_code_str = ft_itoa(exit_code);
	set_env_var(&(*program)->envp, "?", exit_code_str);
	free(exit_code_str);
}

void	execute_pipeline(t_program **program)
{
	t_command	*current_cmd;
	int			pipefd[2];
	int			in_fd;
	int			amount;
	pid_t		pid;

	current_cmd = (*program)->commands;
	in_fd = STDIN_FILENO;
	amount = 0;
	if (count_commands(*program) == 1 && current_cmd->argv[0] &&
		is_builtin(current_cmd->argv[0]))
		execute_builtin_with_redirection((*program)->commands, program);
	else
	{
		while (current_cmd)
		{
			amount++;
			if (current_cmd->next && pipe(pipefd) == -1)
				exit(EXIT_FAILURE);
			pid = fork();
			if (pid == 0)
			{
				if (in_fd != STDIN_FILENO)
				{
					dup2(in_fd, STDIN_FILENO);
					close(in_fd);
				}
				if (current_cmd->next)
				{
					dup2(pipefd[1], STDOUT_FILENO);
					close(pipefd[1]);
				}
				if (current_cmd->next)
					close(pipefd[0]);
				execute_single_command(current_cmd, (*program)->envp);
				exit(EXIT_FAILURE);
			}
			else if (pid > 0)
			{
				if (in_fd != STDIN_FILENO)
					close(in_fd);
				if (current_cmd->next)
				{
					close(pipefd[1]);
					in_fd = pipefd[0];
				}
			}
			else
				exit(EXIT_FAILURE);
			current_cmd = current_cmd->next;
		}
		wait_for_children(amount, program);
	}
}
