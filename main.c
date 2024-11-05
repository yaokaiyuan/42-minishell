#include "shell.h"

void	ft_free_array(char **arr);
t_program	*init_program(char **envp)
{
	t_program	*program;

	program = malloc(sizeof(t_program));
	program->input = NULL;
	program->tokens = NULL;
	program->commands = NULL;
	program->envp = init_env_list(envp);
	return (program);
}

t_command *init_command()
{
    t_command *new_cmd = malloc(sizeof(t_command));
    if (!new_cmd)
        return NULL; // Handle memory allocation failure

    new_cmd->argv = NULL;
    new_cmd->redirects = NULL;
    new_cmd->append = 0;
    new_cmd->next = NULL;
    new_cmd->flag_error = 0;

    return new_cmd;
}

int check_quote(const char *input)
{
    int in_single_quote = 0;
	int in_double_quote = 0;

    while (*input)
	{
        if (*input == '\'' || *input == '\"') 
		{
            in_single_quote = !in_single_quote; // Toggle the state
			in_double_quote = !in_double_quote;
        }
        input++;
    }
    
    // Return 1 if there is an unmatched single quote or if there is only one quote
    return (in_single_quote || in_double_quote);
}

char *process_double_quote(const char *input) {
    // Allocate memory for the result, assuming the worst case where all characters are replaced
    char *result = malloc(strlen(input) + 1); // Allocate enough space for the result
    if (!result) return NULL; // Handle memory allocation failure

    char *ptr = result;
    const char *input_ptr = input;
    int in_double_quote = 0; // Track if we are inside double quotes

    while (*input_ptr) {
        if (*input_ptr == '\"') {
            *ptr++ = *input_ptr++; // Copy the double quote to the result
            in_double_quote = !in_double_quote; // Toggle the state
            continue; // Continue to the next character
        }

        if (*input_ptr == '$' && in_double_quote) { // Only process $ inside double quotes
            input_ptr++; // Move past the dollar sign
            char var_name[256]; // Buffer for variable name
            int i = 0;

            // Extract the variable name
            while (*input_ptr && (ft_isalnum(*input_ptr) || *input_ptr == '_')) {
                var_name[i++] = *input_ptr++;
            }
            var_name[i] = '\0'; // Null-terminate the variable name

            // Get the environment variable value
            char *env_value = getenv(var_name);
            if (env_value) {
                // Copy the environment variable value to the result
                strcpy(ptr, env_value);
                ptr += strlen(env_value); // Move the pointer forward
            }
        } else {
            *ptr++ = *input_ptr++; // Copy the character to the result
        }
    }

    *ptr = '\0'; // Null-terminate the result string
    return result; // Return the processed string
}

char *strip_quotes(char *token) {
    size_t len = strlen(token);
    if ((token[0] == '\'' && token[len - 1] == '\'') || (token[0] == '"' && token[len - 1] == '"')) {
        token[len - 1] = '\0'; // Remove trailing quote
        token++; // Move past leading quote
    }
    return token;
}

void parse_commands(t_program *program)
{
	if (check_quote(program->input))
	{
		ft_putstr_fd("minishell: unmatched quotes\n", STDERR_FILENO);
		return ;
	}
	char *processed_input = process_double_quote(program->input);
    if (processed_input) {
        free(program->input); // Free the old input
        program->input = processed_input; // Update to the processed input
    }
    // Initialize tokens using ft_strtok
    program->tokens = ft_strtok(program->input, " ");
    t_command *current_cmd = NULL;
    t_command *head = NULL;

    while (program->tokens != NULL) // Loop until no more tokens
    {
		char *token = strip_quotes(program->tokens);
        if (ft_strncmp(token, "|", 1) == 0)
        {
            // Initialize a new command for each pipe
            if (!head)
            {
                head = init_command();
                current_cmd = head;
            }
            else
            {
                current_cmd->next = init_command();
                current_cmd = current_cmd->next;
            }
        }
        else if (ft_strncmp(token, ">", 1) == 0 || ft_strncmp(token, "<", 1) == 0 || ft_strncmp(token, ">>", 2) == 0)
        {
            // Ensure current_cmd is initialized
            if (!current_cmd) {
                ft_putstr_fd("minishell: syntax error near unexpected token\n", STDERR_FILENO);
                break;
            }
            // Handle redirections
            t_redirection_type type = (ft_strncmp(program->tokens, ">", 1) == 0) ? REDIRECT_OUT : REDIRECT_IN;
            if (ft_strncmp(program->tokens, ">>", 2) == 0)
                current_cmd->append = 1;

            // Get the next token for the file name
            program->tokens = ft_strtok(NULL, " ");
            if (program->tokens != NULL)
            {
                t_redirection *new_redirection = malloc(sizeof(t_redirection));
                new_redirection->file = ft_strdup(program->tokens);
                new_redirection->type = type;
                // new_redirection->next = current_cmd->redirects;
                // current_cmd->redirects = new_redirection;

                new_redirection->next = NULL;
                if (current_cmd->redirects == NULL)
                {
                    current_cmd->redirects = new_redirection;
                }
                else
                {
                    t_redirection *tmp = current_cmd->redirects;
                    while (tmp->next != NULL)
                    {
                        tmp = tmp->next;
                    }
                    tmp->next = new_redirection;
                }
            }
            else
            {
                ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
                break;
            }
        }
        else
        {
            // Ensure current_cmd is initialized
            if (!current_cmd) {
                current_cmd = init_command();
                if (!head) {
                    head = current_cmd;
                }
            }
            // Add arguments to the current command
            int argc = 0;
            while (current_cmd->argv && current_cmd->argv[argc])
                argc++;
            
            // Allocate memory for new_argv, including space for the new argument and NULL terminator
            char **new_argv = ft_realloc(current_cmd->argv, sizeof(char *) * (argc + 2));
            if (!new_argv) {
                perror("ft_realloc failed");
                exit(EXIT_FAILURE); // TODO replace with clean_exit
            }

            new_argv[argc] = ft_strdup(token);
            if (!new_argv[argc]) {
                perror("ft_strdup failed");
                exit(EXIT_FAILURE); // TODO replace with clean_exit
            }
            new_argv[argc + 1] = NULL;
            current_cmd->argv = new_argv;
        }

        // Get the next token
        program->tokens = ft_strtok(NULL, " ");
    }

    program->commands = head;
}

void	free_program(t_program *program)
{
	if (program->input)
		free(program->input);
	if (program->tokens)
		free(program->tokens);
	if (program->envp)
		clean_env_list(program->envp);
	free(program);
}

void	ft_free_array(char **arr)
{
	char	**tmp;

	tmp = arr;
	while (*arr)
	{
		if (*arr)
			free(*arr);
		arr++;
	}
	free(tmp);
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    t_program	*program;

    program = init_program(envp);
    handle_signals();
    while (1)
    {
        program->input = readline("minishell>");
		// e.g. input = `$ENV_VAR=23 echo    "$SHLVL"`
		// trim(input), set_env_var(env-var)
		// =>
		// input = `echo 2`

        if (!program->input) // FREE AND EXIT
            break ;
        if (is_heredoc(program->input))
        {
            program->input = handle_heredoc(program->input);
            if (!program->input) // FREE AND EXIT
                break ;
        }
        parse_commands(program);
        execute_pipeline(&program);
        if (program->input)
            add_history(program->input);
        free(program->input);
        free(program->tokens);
        // free_commands();
    }

    free_program(program);
    return 0;
}