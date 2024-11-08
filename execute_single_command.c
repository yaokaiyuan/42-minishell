#include "shell.h"

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
	cmd_path = NULL;
	if (cmd->argv[0][0] == '/' || cmd->argv[0][0] == '.')
	{
		if (access(cmd->argv[0], X_OK) == 0)
			cmd_path = ft_strdup(cmd->argv[0]);
		else
		{
			perror(cmd->argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		// Реализация поиска команды в PATH
		char *path_value = get_env_value(env_list, "PATH");
		if (path_value)
		{
			// Split PATH into directories
			char **paths = ft_split(path_value, ':');
			int i = 0;
			while (paths[i])
			{
				// Construct the full path
				char *full_path = malloc(ft_strlen(paths[i]) + 1 + ft_strlen(cmd->argv[0]) + 1);
				if (full_path)
				{
					size_t path_len = ft_strlen(paths[i]);
					size_t cmd_len = ft_strlen(cmd->argv[0]);
					ft_memcpy(full_path, paths[i], path_len);
					full_path[path_len] = '/';
					ft_memcpy(full_path + path_len + 1, cmd->argv[0], cmd_len + 1);
				}
				// Check if the command exists and is executable
				if (access(full_path, X_OK) == 0)
				{
					cmd_path = full_path;
					break;
				}
				free(full_path);
				i++;
			}
			clean_str_arr(paths);
		}
		if (!cmd_path)
		{
			ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			exit(127); // Command not found
		}
	}
	if (!cmd_path)
	{
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	execve(cmd_path, cmd->argv, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}
