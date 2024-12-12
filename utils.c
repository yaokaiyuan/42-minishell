#include "shell.h"

void	clean_str_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (0);
	}
	new_ptr = malloc(size);
	if (!new_ptr)
		exit(EXIT_FAILURE);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

void	ft_free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_redirections(t_redirection *redirects)
{
	t_redirection	*current;
	t_redirection	*next;

	current = redirects;
	while (current)
	{
		next = current->next;
		free(current->file);
		free(current);
		current = next;
	}
}

void	free_commands(t_command *commands)
{
	t_command	*current;
	t_command	*next;

	current = commands;
	while (current)
	{
		next = current->next;
		if (current->argv)
			ft_free_array(current->argv);
		free_redirections(current->redirects);
		if (current)
			free(current);
		current = next;
	}
}
