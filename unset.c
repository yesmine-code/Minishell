/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:50:08 by mrahmani          #+#    #+#             */
/*   Updated: 2021/11/14 13:13:43 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_unset(t_env **env_list, char **list_to_delete)
{
    int i;

    i = 1;
    if (env_list == NULL)
        return (-1);
    if (list_to_delete[i] == NULL)
    {
        printf("unset: %s: invalid parameter name\n", list_to_delete[i]);
        return (-1);
    }
    while (list_to_delete && list_to_delete[i])
    {
        if (is_new_env(list_to_delete[i]) == 1 || list_to_delete[1] == NULL)
        {
            printf("unset: %s: invalid parameter name\n", list_to_delete[i]);
            return (-1);
        }
        delete_env(env_list, list_to_delete[i]);
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