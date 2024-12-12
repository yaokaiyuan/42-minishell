#include "shell.h"

void	handle_child_process(t_command *current_cmd, int in_fd, int *pipefd,
	t_program **program)
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

void	handle_parent_process(pid_t pid, t_command *current_cmd,
	int *in_fd, int *pipefd)
{
	if (pid > 0)
	{
		if (*in_fd != STDIN_FILENO)
			close(*in_fd);
		if (current_cmd->next)
		{
			close(pipefd[1]);
			*in_fd = pipefd[0];
		}
	}
	else
		exit(EXIT_FAILURE);
}

void	run_command_loop(t_program **program)
{
	t_command	*current_cmd;
	int			in_fd;
	int			pipefd[2];
	pid_t		pid;
	int			amount;

	current_cmd = (*program)->commands;
	in_fd = STDIN_FILENO;
	amount = 0;
	while (current_cmd)
	{
		amount++;
		if (current_cmd->next && pipe(pipefd) == -1)
			exit(EXIT_FAILURE);
		pid = fork();
		if (pid == 0)
			handle_child_process(current_cmd, in_fd, pipefd, program);
		else
			handle_parent_process(pid, current_cmd, &in_fd, pipefd);
		current_cmd = current_cmd->next;
	}
	wait_for_children(amount, program);
}
