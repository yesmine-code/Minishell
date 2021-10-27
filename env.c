/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 20:04:27 by mrahmani          #+#    #+#             */
/*   Updated: 2021/10/27 20:14:44 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(char **env)
{
    int index = 0;

    if (env == NULL)
        return (-1);
    while (env[index])
    {
        printf("%s\n", env[index++]);
    }
    return (0);
}