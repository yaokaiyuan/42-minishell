#include "shell.h"

void	handle_input_redirection(t_redirection *current_redirection)
{
	int	fd;

	fd = open(current_redirection->file, O_RDONLY);
	if (fd < 0)
	{
		perror(current_redirection->file);
		return ;
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, 0) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	handle_output_redirection(
	t_redirection *current_redirection, int append)
{
	int	fd;

	if (append)
		fd = open(
				current_redirection->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(
				current_redirection->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(current_redirection->file);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, 1) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	handle_redirection(t_command *cmd)
{
	t_redirection	*current_redirection;

	current_redirection = cmd->redirects;
	while (current_redirection)
	{
		if (current_redirection->type == REDIRECT_IN)
			handle_input_redirection(current_redirection);
		else if (current_redirection->type == REDIRECT_OUT)
			handle_output_redirection(current_redirection, cmd->append);
		current_redirection = current_redirection->next;
	}
}

int	is_builtin(const char *command)
{
	const char	*builtins[] = {"echo", "cd", "pwd", "export",
		"unset", "env", "exit", "$?", NULL};
	int			i;

	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(command, builtins[i], ft_strlen(builtins[i]) + 1) == 0)
			return (1);
		i++;
	}
	return (0);
}
