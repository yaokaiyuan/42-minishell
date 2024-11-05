#include "shell.h"

void clean_str_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return ;
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
		return (0);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}