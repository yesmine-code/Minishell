/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:50:08 by mrahmani          #+#    #+#             */
/*   Updated: 2021/11/19 00:17:54 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_exist(char *to_delte, t_env *list_env)
{
    t_env *tmp;

    tmp = list_env;
    if (ft_strncmp(tmp->name, to_delte, ft_strlen(tmp->name)) == 0)
        return (1);
    while (tmp->next != NULL)
    {
        if (ft_strncmp(tmp->name, to_delte, ft_strlen(tmp->name)) == 0)
            return (1);
        tmp = tmp->next;
    }
    if (ft_strncmp(tmp->name, to_delte, ft_strlen(tmp->name)) == 0)
        return (1);
    return (0);
}

int is_valid_identifier(char *to_delete)
{
    int i;

    i = 0;
    if (to_delete == NULL)
        return (0);
    while (to_delete[i])
    {
        if (to_delete[i] == '_')
            i++;
        else if (to_delete[i] == '=' || (i == 0 && ft_isdigit(to_delete[i]) == 1) || ft_isalnum(to_delete[i]) == 0)
            return (0);
        i++;
    }
    return (1);
}

int ft_unset(t_env **env_list, char **list_to_delete)
{
    int i;

    i = 1;
    if (env_list == NULL)
        return (-1);
    while (list_to_delete[i] != NULL)
    {
        if (is_valid_identifier(list_to_delete[i]) == 0)
        {
            printf("unset: '%s': not a valid identifier\n", list_to_delete[i]);
            i++;
        }
        else if (is_exist(list_to_delete[i], *env_list) == 1)
        {
            delete_env(env_list, list_to_delete[i]);
            i++;
        }
        else
            i++;
    }
    return (1);
}

void delete_env(t_env **env_list, char *to_delete)
{
    t_env *tmp;
    t_env *previous;

    tmp = *env_list;
    previous = NULL;
    {
        if (ft_strncmp(tmp->name, to_delete, ft_strlen(to_delete)) == 0)
        {
            *env_list = (*env_list)->next;
            free(tmp);
            return;
        }
        previous = tmp;
        while (tmp != NULL)
        {
            if (ft_strncmp(tmp->name, to_delete, ft_strlen(to_delete)) == 0)
            {
                previous->next = tmp->next;
                free(tmp);
                return;
            }
            previous = tmp;
            tmp = tmp->next;
        }
    }
}