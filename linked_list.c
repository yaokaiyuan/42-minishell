#include "shell.h"

t_list *init_env_list(char **envp)
{
    t_list *env_list = NULL;
    int shlvl_found = 0;

    for (int i = 0; envp[i] != NULL; i++)
    {
        if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
        {
            int level = ft_atoi(envp[i] + 6);
            char *new_shlvl = ft_itoa(level + 1);
            char *env_var = ft_strjoin("SHLVL=", new_shlvl);
            t_list *new_node = ft_lstnew(ft_strdup(env_var));
            ft_lstadd_back(&env_list, new_node);
            free(new_shlvl);
            free(env_var);
            shlvl_found = 1;
        }
        else
        {
            t_list *new_node = ft_lstnew(ft_strdup(envp[i]));
            ft_lstadd_back(&env_list, new_node);
        }
    }

    if (!shlvl_found)
    {
        char *env_var = ft_strdup("SHLVL=1");
        t_list *new_node = ft_lstnew(env_var);
        ft_lstadd_back(&env_list, new_node);
    }

    return env_list;
}

void add_env_var(t_list **env_list, const char *var)
{
	t_list *new_node = ft_lstnew(ft_strdup(var));
	ft_lstadd_back(env_list, new_node);
}

void remove_env_var(t_list **env_list, const char *key)
{
	t_list *current = *env_list;
	t_list *prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->content, key, ft_strlen(key)) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			ft_lstdelone(current, free);
			return;
		}
		prev = current;
		current = current->next;
	}
}

void clean_env_list(t_list *env_list)
{
	ft_lstclear(&env_list, free);
}

char **convert_env_list_to_array(t_list *env_list)
{
    int count = 0;
    t_list *temp = env_list;
    while (temp)
    {
        count++;
        temp = temp->next;
    }

    char **envp = malloc((count + 1) * sizeof(char *));
    if (!envp)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    temp = env_list;
    while (temp)
    {
        envp[i] = strdup(temp->content);
        if (!envp[i])
        {
            perror("strdup");
            exit(EXIT_FAILURE); // todo clean
        }
        temp = temp->next;
        i++;
    }
    envp[i] = NULL;

    return envp;
}