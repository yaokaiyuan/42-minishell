#include "shell.h"

int last_exit_status = 0;

void	handle_input_redirection(t_redirection *current_redirection)
{
	int	fd;

	fd = open(current_redirection->file, O_RDONLY);
	if (fd < 0)
	{
		perror(current_redirection->file);
		exit(EXIT_FAILURE);
	}
	dup2(fd, 0);
	close(fd);
}

void	handle_output_redirection(t_redirection *current_redirection, int append)
{
	int	fd;

	if (append)
	{
		fd = open(current_redirection->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		fd = open(current_redirection->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (fd < 0)
	{
		perror(current_redirection->file);
		exit(EXIT_FAILURE);
	}
	dup2(fd, 1);
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

int is_builtin(const char *command)
{
    const char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
    int i = 0;
    while (builtins[i])
    {
        if (ft_strncmp(command, builtins[i], ft_strlen(builtins[i]) + 1) == 0)
            return 1;
        i++;
    }
    return 0;
}

// Execute the built-in command
void execute_builtin_command(t_command *cmd, t_list *env_list)
{
    if (ft_strncmp(cmd->argv[0], "echo", 4) == 0)
    {
        builtin_echo(cmd->argv);
    }
    else if (ft_strncmp(cmd->argv[0], "cd", 2) == 0)
    {
        builtin_cd(cmd->argv, env_list);
    }
    else if (ft_strncmp(cmd->argv[0], "pwd", 3) == 0)
    {
        builtin_pwd();
    }
    else if (ft_strncmp(cmd->argv[0], "export", 6) == 0)
    {
        builtin_export(cmd->argv, env_list);
    }
    else if (ft_strncmp(cmd->argv[0], "unset", 5) == 0)
    {
        builtin_unset(cmd->argv);
    }
    else if (ft_strncmp(cmd->argv[0], "env", 3) == 0)
    {
        builtin_env(env_list);
    }
    else if (ft_strncmp(cmd->argv[0], "exit", 4) == 0)
    {
        builtin_exit();
    }
}

void execute_single_command(t_command *cmd, t_list *env_list)
{
    handle_redirection(cmd);
    if (is_builtin(cmd->argv[0]))
    {
        execute_builtin_command(cmd, env_list);
    }
    else
    {
        execvp(cmd->argv[0], cmd->argv);
        perror("execvp");
        exit(EXIT_FAILURE); // TODO clean
    }
}

void	execute_builtin_with_redirection(t_command *cmd, t_program **program)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(1);
	saved_stdin = dup(0);
	if (saved_stdout == -1 || saved_stdin == -1)
	{
		perror("Failed to save STDIN or STDOUT");
		exit(EXIT_FAILURE);
	}
	dup2((*program)->in_fd, 0);
	dup2((*program)->out_fd, 1);
	handle_redirection(cmd);
	execute_builtin_command(cmd, (*program)->envp);

    dup2(saved_stdin, 0);
	dup2(saved_stdout, 1);
	close(saved_stdin);
	close(saved_stdout);
}

int count_commands(t_program *program)
{
    int i;
    t_command *current_cmd;
    
    current_cmd = program->commands;
    i = 0;
    while (current_cmd)
    {
        current_cmd = current_cmd->next;
        i++;
    }
    return (i);
}

void execute_pipeline(t_program **program)
{
    t_command *current_cmd = (*program)->commands;
    int pipefd[2];
    int in_fd = STDIN_FILENO;
    pid_t pid;

    if (count_commands(*program) == 1 && current_cmd->argv[0]
		&& is_builtin(current_cmd->argv[0]))
    {
        execute_builtin_with_redirection((*program)->commands, program);
    }
    else
    {
        while (current_cmd != NULL)
        {
            if (current_cmd->next != NULL)
            {
                if (pipe(pipefd) == -1)
                {
                    perror("pipe");
                    exit(EXIT_FAILURE);
                }
            }

            pid = fork();
            if (pid == 0)
            {
                // Child process
                dup2(in_fd, STDIN_FILENO); // Redirect stdin
                if (current_cmd->next != NULL)
                {
                    dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
                }
                close(pipefd[0]); // Close unused read end
                execute_single_command(current_cmd, (*program)->envp);
                exit(EXIT_FAILURE);
            }
            else if (pid > 0)
            {
                // Parent process
                wait(NULL); // Wait for child process
                close(pipefd[1]); // Close write end
                in_fd = pipefd[0]; // Use read end for next command
                (*program)->in_fd = pipefd[0];
            }
            else
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }

            current_cmd = current_cmd->next;
        }
    }
}

void sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    // rl_replace_line("", 0); // works on linux
    rl_redisplay();
}

void handle_signals(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}
