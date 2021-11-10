/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 10:21:10 by mrahmani          #+#    #+#             */
/*   Updated: 2021/11/10 13:42:20 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_exit(char *s, t_env *env)
{
    t_env *tmp;

    tmp = env;
    while (tmp->next != NULL)
    {
        if (ft_strncmp(tmp->name, get_name_env(s), ft_strlen(tmp->name) == 0))
            return (1);
        tmp = tmp->next;
    }
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

int ft_export(t_env *env, char **arg)
{
    t_env *new;

   // if (is_new_env(arg[1]) == 1 && is_exit(arg[1], env) == 0)
   // {
        new = malloc(sizeof(t_env));
        if (new == NULL)
            return (NULL);
        add_env(&env, new, arg[1]);
       // ft_env(env);
        return (1);
    //}
    // else if (is_new_env(arg[1]) == 1 && is_exit(arg[1], env) == 1)
    // {
    //     while (env->next != NULL)
    //     {
    //         if (ft_strncm(env->name, get_name_env(arg[1]), ft_strlen(env->name)) == 0)
    //              env->var = ft_strjoin(env->name, get_value(arg[1]));
    //     }
        
    // }
}
