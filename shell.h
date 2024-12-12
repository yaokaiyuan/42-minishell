/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:07:50 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/12/12 18:43:08 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include "./libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>

typedef enum e_redirection_type
{
	REDIRECT_IN = 1,
	REDIRECT_OUT,
}	t_redirection_type;

typedef struct s_redirection
{
	char					*file;
	t_redirection_type		type;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_command
{
	char					**argv;
	t_redirection			*redirects;
	int						append;
	struct s_command		*next;
	int						flag_error;
	int						ret;
}	t_command;

typedef struct s_program
{
	char		*input;
	char		*tokens;
	t_command	*commands;
	t_list		*envp;
	int			in_fd;
	int			out_fd;
}	t_program;

/* Initialization functions */
t_program	*init_program(char **envp);
t_command	*init_command(void);

/* Parsing functions */
void		parse_commands(t_program *program);
int			get_env_var_length(const char **input_ptr);
int			get_expanded_length(const char *input);
char		*handle_dollar_sign(
				t_program *program, const char **input_ptr, char *ptr);
char		*process_double_quote(t_program *program);
char		*strip_quotes(char *token);
char		*ft_strtok(char *str, const char *delim);
char 		*process_redirections_outside_quotes(char *input);

/* Execution functions */
void		execute_pipeline(t_program **program);
void		execute_builtin_with_redirection(t_command *cmd,
				t_program **program);
void		execute_builtin_command(t_command *cmd,
				t_list *env_list);
void		execute_single_command(t_command *cmd, t_list *env_list);
void		wait_for_children(int num_commands, t_program **program);
void		handle_child_process(t_command *current_cmd, int in_fd, int *pipefd,
				t_program **program);
void		handle_parent_process(pid_t pid, t_command *current_cmd,
				int *in_fd, int *pipefd);
void		run_command_loop(t_program **program);
int			is_builtin(const char *command);

/* Built-in commands */
void		builtin_echo(char **args);
void		builtin_cd(char **args, t_list *env_list);
void		builtin_pwd(void);
void		builtin_export(char **args, t_list *env_list);
void		builtin_unset(char **args, t_list *env_list);
void		builtin_env(t_list *env_list);
void		builtin_exit(char **args);

/* Redirection handling */
void		handle_redirection(t_command *cmd);
void		handle_input_redirection(t_redirection *current_redirection);
void		handle_output_redirection(t_redirection *current_redirection,
				int append);
void		handle_redirection_token(t_program *program, t_command *current_cmd,
				char *token);

/* Environment variables */
t_list		*init_env_list(char **envp);
void		add_env_var(t_list **env_list, const char *var);
void		set_env_var(t_list **env_list, const char *key, const char *value);
void		remove_env_var(t_list **env_list, const char *key);
void		clean_env_list(t_list *env_list);
char		*get_env_value(t_list *env_list, const char *key);
char		**convert_env_list_to_array(t_list *env_list);

/* Heredoc handling */
int			is_heredoc(char *input);
char		*handle_heredoc(char *input);
char		*append_line_to_heredoc_content(
				char *heredoc_content, char *line, size_t *total_len);
void		write_heredoc_to_file(const char *filename, const char *content);

/* Utility functions */
void		clean_str_arr(char **arr);
void		*ft_realloc(void *ptr, size_t size);
void		ft_free_array(char **arr);
void		free_redirections(t_redirection *redirects);
void		free_commands(t_command *commands);
void		free_program(t_program *program);
void		sigint_handler(int sig);
void		handle_sigquit(int sig);
void		handle_sigint_blocking(int sig);
char		*generate_unique_filename(void);

#endif
