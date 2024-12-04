#include "shell.h"

void	builtin_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[i] && ft_strncmp(args[i], "-n", 3) == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		free(cwd);
	}
	else
		perror("pwd");
}

void	builtin_env(t_list *env_list)
{
	t_list	*temp;

	temp = env_list;
	while (temp)
	{
		if (((char *)temp->content)[0] != '?')
			ft_putendl_fd(temp->content, STDOUT_FILENO);
		temp = temp->next;
	}
}

void	builtin_exit(void)
{
	// TODO 2 args or more -> do nothing, exit: too many arguments
	// TODO add the exit code as an argument: exit 123 -> $? -> 123
	// exit Hello -> exit: hello: numeric argument required 
		// ykai-yua@z1t1c1 ~/Desktop/minishell 
		// % $? 
		// zsh: command not found: 2
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}
