#include "shell.h"

void builtin_echo(char **args)
{
    for (int i = 1; args[i]; i++)
    {
        if (i > 1)
            printf(" ");
        printf("%s", args[i]);
    }
    printf("\n");
}

void builtin_cd(char **args, t_list *env_list)
{
    char *oldpwd = getcwd(NULL, 0);
    if (args[1] == NULL || chdir(args[1]) != 0)
    {
        perror("cd");
    }
    else
    {
        char *newpwd = getcwd(NULL, 0);
        remove_env_var(&env_list, "OLDPWD");
        add_env_var(&env_list, ft_strjoin("OLDPWD=", oldpwd));
        remove_env_var(&env_list, "PWD");
        add_env_var(&env_list, ft_strjoin("PWD=", newpwd));
        free(newpwd);
    }
    free(oldpwd);
}

void builtin_pwd(void)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("getcwd");
}

void builtin_export(char **args, t_list *env_list)
{
    if (args[1] == NULL)
    {
        t_list *current = env_list;
        while (current)
        {
            printf("%s\n", (char *)current->content);
            current = current->next;
        }
    }
    else
    {
        add_env_var(&env_list, args[1]);
    }
}

void builtin_unset(char **args)
{
    if (args[1] == NULL)
    {
        perror("unset: not enough arguments\n");
    }
    else
    {
        if (unsetenv(args[1]) != 0)
            perror("unset");
    }
}

void builtin_env(t_list *env_list)
{
    t_list *current = env_list;
    while (current)
    {
        printf("%s\n", (char *)current->content);
        current = current->next;
    }
}

void builtin_exit(void)
{
    ft_putstr_fd("minishell: exit\n", 1);
    exit(0);
}
