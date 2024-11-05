#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include "./libft/libft.h"
#include <sys/types.h>
#include <sys/wait.h>

// Definition of a Binary Tree Node
typedef struct Node {
    char* command; // Command string
    char** args;   // Arguments array
    char* input_redirection; // Input redirection file
    char* output_redirection; // Output redirection file
    char* append_redirection; // Append redirection file
    char* here_doc_redirection; // Here document redirection file
    struct Node* left; // Left child (for pipes)
    struct Node* right; // Right child (for next command)
} Node;

typedef enum e_redirection_type
{
	REDIRECT_IN = 1,
	REDIRECT_OUT,
}							t_redirection_type;

typedef struct s_redirection
{
	char					*file;
	t_redirection_type		type;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_command
{
	char					**argv;
	t_redirection			*redirects;
	int						append;
	struct s_command		*next;
	int						flag_error;
	int						ret;
}							t_command;

typedef struct s_program
{
	char					*input;
  	char                    *tokens;
	t_command				*commands;
	t_list					*envp;
	int						in_fd;
	int						out_fd;
}							t_program;

void	display_prompt(void);
void	execute_pipeline(t_program **program);
void	execute_builtin_with_redirection(t_command *cmd, t_program **program);
char	*handle_heredoc(char *input);
int		is_heredoc(char *input);
void	handle_signals(void);
void	builtin_echo(char **args);
void	builtin_cd(char **args, t_list *env_list);
void	builtin_pwd(void);
void	builtin_export(char **args, t_list *env_list);
void	builtin_unset(char **args);
void	builtin_env(t_list *env_list);
void	builtin_exit(void);
void	clean_str_arr(char **arr);
void	add_env_var(t_list **env_list, const char *var);
void	remove_env_var(t_list **env_list, const char *key);
void	clean_env_list(t_list *env_list);
void	*ft_realloc(void *ptr, size_t size);
t_list	*init_env_list(char **envp);
char	*ft_strtok(char* str, const char* delim);
int 	check_quote(const char *input);
char	*process_double_quote(const char *input);

#endif