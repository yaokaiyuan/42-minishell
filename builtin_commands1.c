#include "shell.h"

void	builtin_cd(char **args, t_list *env_list)
{
	char		*path;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		set_env_var(&env_list, "OLDPWD", cwd);
		free(cwd);
	}
	if (!args[1])
		path = get_env_value(env_list, "HOME");
	else
		path = args[1];
	// TODO check if there is only 1 argument -> cd: too many arguments
	if (chdir(path) != 0)
		perror("cd");
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		set_env_var(&env_list, "PWD", cwd);
		free(cwd);
	}
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
	if (i == 1)
	{
		builtin_env(env_list);
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
