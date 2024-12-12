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

static int	ft_is_numeric_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	builtin_exit(char **args)
{
	int	exit_code;

	if (args[1] && args[2])
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return ;
	}
	if (args[1])
	{
		if (!ft_is_numeric_string(args[1]))
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			return ;
		}
		else
			exit_code = ft_atoi(args[1]);
	}
	else
		exit_code = EXIT_SUCCESS;
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(exit_code);
}
