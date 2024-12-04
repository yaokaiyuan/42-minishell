#include "shell.h"

void set_env_var(t_list **env_list, const char *key, const char *value)
{
	size_t len;
	char *tmp;

	len = ft_strlen(key) + ft_strlen(value) + 2;
	tmp = malloc(len);
	if (!tmp)
		exit(EXIT_FAILURE); // TODO free and exit
	ft_strlcpy(tmp, key, len);
	ft_strlcat(tmp, "=", len);
	ft_strlcat(tmp, value, len);
	add_env_var(env_list, tmp);
	free(tmp);
}