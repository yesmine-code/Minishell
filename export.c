/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 10:21:10 by mrahmani          #+#    #+#             */
/*   Updated: 2021/11/19 00:20:15 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exists(char *s, t_env *env, t_env **new_env)
{
    t_env *tmp;
    char *name_of_new_env;

    tmp = env;
    name_of_new_env = get_name_env(s);
    while (tmp->next != NULL)
    {
        if (ft_strncmp(tmp->name, name_of_new_env, ft_strlen(tmp->name)) == 0)
        {
            free(name_of_new_env);
            *new_env = tmp;
            return (1);
        }
        tmp = tmp->next;
    }
    if (ft_strncmp(tmp->name, name_of_new_env, ft_strlen(tmp->name)) == 0)
    {
        free(name_of_new_env);
        *new_env = tmp;
        return (1);
    }
    free(name_of_new_env);
    return (0);
}

int is_new_env(char *s)
{
    int i;

    i = 0;
    if (s == NULL)
        return (0);
    while (s[i])
    {
        if (s[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

int is_valid_env(char *s)
{
    int i;

    i = 0;
    if (s == NULL)
        return (0);
    while (s[i])
    {
        if (s[i] == '_')
            i++;
        else if (ft_isalnum(s[i]) == 0 || (i == 0 && ft_isdigit(s[i]) == 1))
            return (0);
        i++;
    }
    return (1);
}

int check_error(char *s)
{
    char *env_name;
    if (s == NULL)
        return (0);
    env_name = get_name_env(s);
    if (is_valid_env(env_name) == 0)
    {
        printf("export: '%s': not a valid identifier\n", s);
        free(env_name);
        return (0);
    }
    free(env_name);
    return (1);
}

int ft_export(t_env *env, char **arg)
{
    t_env *new;
    t_env *new_env;
    t_env *env_to_update;
    int i;

    i = 1;
    if (arg[1] == NULL)
        return ft_env(env);
    while (arg[i] != NULL)
    {
        if (check_error(arg[i]) == 0)
            i++;
        else if (arg[i] != NULL && is_new_env(arg[i]) == 1)
        {
            if (exists(arg[i], env, &new_env) == 0)
            {
                new = malloc(sizeof(t_env));
                if (new == NULL)
                    return (-1);
                add_env(&env, new, arg[i]);
            }
            else if (exists(arg[i], env, &env_to_update) == 1)
                env_to_update->var = arg[i];
            i++;
        }
        else
            i++;
    }
    return (1);
}
