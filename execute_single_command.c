#include "shell.h"

static char	*try_absolute_path(t_command *cmd)
{
	if (access(cmd->argv[0], X_OK) == 0)
		return (ft_strdup(cmd->argv[0]));
	perror(cmd->argv[0]);
	exit(EXIT_FAILURE);
}

static char	*check_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;
	size_t	path_len;
	size_t	cmd_len;

	i = 0;
	while (paths[i])
	{
		path_len = ft_strlen(paths[i]);
		cmd_len = ft_strlen(cmd);
		full_path = malloc(path_len + cmd_len + 2);
		if (full_path)
		{
			ft_memcpy(full_path, paths[i], path_len);
			full_path[path_len] = '/';
			ft_memcpy(full_path + path_len + 1, cmd, cmd_len + 1);
			if (access(full_path, X_OK) == 0)
				return (full_path);
			free(full_path);
		}
		i++;
	}
	return (NULL);
}

static char	*find_cmd_path(t_command *cmd, t_list *env_list)
{
	char	*path_value;
	char	**paths;
	char	*cmd_path;

	cmd_path = NULL;
	if (cmd->argv[0][0] == '/' || cmd->argv[0][0] == '.')
		return (try_absolute_path(cmd));
	path_value = get_env_value(env_list, "PATH");
	if (path_value)
	{
		paths = ft_split(path_value, ':');
		if (!paths)
			exit(EXIT_FAILURE);
		cmd_path = check_paths(paths, cmd->argv[0]);
		clean_str_arr(paths);
	}
	if (!cmd_path)
	{
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	return (cmd_path);
}

void	execute_single_command(t_command *cmd, t_list *env_list)
{
	char	**envp;
	char	*cmd_path;

	handle_redirection(cmd);
	if (is_builtin(cmd->argv[0]))
	{
		execute_builtin_command(cmd, env_list);
		exit(EXIT_SUCCESS);
	}
	envp = convert_env_list_to_array(env_list);
	if (!envp)
		exit(EXIT_FAILURE);
	cmd_path = find_cmd_path(cmd, env_list);
	execve(cmd_path, cmd->argv, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}
