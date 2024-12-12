#include "shell.h"

char	**convert_env_list_to_array(t_list *env_list)
{
	char	**envp;
	t_list	*temp;
	int		count;
	int		i;

	count = ft_lstsize(env_list);
	envp = malloc((count + 1) * sizeof(char *));
	if (!envp)
		exit(EXIT_FAILURE);
	i = 0;
	temp = env_list;
	while (temp)
	{
		envp[i] = ft_strdup(temp->content);
		if (!envp[i])
			exit(EXIT_FAILURE);
		temp = temp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
