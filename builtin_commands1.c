#include "shell.h"

static void	save_pwd_vars(t_list **env_list, char *oldpwd)
{
	char	*cwd;

	if (oldpwd)
	{
		set_env_var(env_list, "OLDPWD", oldpwd);
		free(oldpwd);
	}
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		set_env_var(env_list, "PWD", cwd);
		free(cwd);
	}
}

static void	actual_cd(char *path, t_list *env_list)
{
	char	*tmp;

	if (ft_strncmp(path, "-", 2) == 0)
	{
		tmp = get_env_value(env_list, "OLDPWD");
		if (chdir(tmp) != 0)
			perror("cd");
		ft_putstr_fd(tmp, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else if (chdir(path) != 0)
		perror("cd");
}

void	builtin_cd(char **args, t_list *env_list)
{
	char		*path;
	char		*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!args[1])
		path = get_env_value(env_list, "HOME");
	else
	{
		if (args[2])
		{
			ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
			if (oldpwd)
				free(oldpwd);
			return ;
		}
		path = args[1];
	}
	actual_cd(path, env_list);
	save_pwd_vars(&env_list, oldpwd);
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
