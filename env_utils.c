#include "shell.h"

t_list	*init_env_list(char **envp)
{
	t_list	*env_list;
	t_list	*new_node;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = ft_lstnew(ft_strdup(envp[i]));
		if (!new_node || !new_node->content)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&env_list, new_node);
		i++;
	}
	add_env_var(&env_list, "?=0");
	return (env_list);
}

void	add_env_var(t_list **env_list, const char *var)
{
	t_list	*new_node;

	new_node = ft_lstnew(ft_strdup(var));
	if (!new_node || !new_node->content)
		exit(EXIT_FAILURE);
	ft_lstadd_back(env_list, new_node);
}

void	remove_env_var(t_list **env_list, const char *key)
{
	t_list	*current;
	t_list	*prev;
	size_t	key_len;

	current = *env_list;
	prev = NULL;
	key_len = ft_strlen(key);
	while (current)
	{
		if (ft_strncmp(current->content, key, key_len) == 0 &&
			((char *)current->content)[key_len] == '=')
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			ft_lstdelone(current, free);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	clean_env_list(t_list *env_list)
{
	ft_lstclear(&env_list, free);
}

char	*get_env_value(t_list *env_list, const char *key)
{
	t_list	*temp;
	size_t	key_len;

	temp = env_list;
	key_len = strlen(key);
	while (temp)
	{
		if (ft_strncmp(temp->content, key, key_len) == 0 &&
			((char *)temp->content)[key_len] == '=')
			return (((char *)temp->content) + key_len + 1);
		temp = temp->next;
	}
	return (NULL);
}
