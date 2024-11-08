#include "shell.h"

void	builtin_cd(char **args, t_list *env_list)
{
	char	*path;

	if (!args[1])
		path = get_env_value(env_list, "HOME");
	else
		path = args[1];
	if (chdir(path) != 0)
		perror("cd");
}

void	builtin_export(char **args, t_list *env_list)
{
	int		i;

	i = 1;
	while (args[i])
	{
		add_env_var(&env_list, args[i]);
		i++;
	}
}

void	builtin_unset(char **args, t_list *env_list)
{
	int		i;

	i = 1;
	while (args[i])
	{
		remove_env_var(&env_list, args[i]);
		i++;
	}
}
