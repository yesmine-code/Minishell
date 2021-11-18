/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:47:03 by mrahmani          #+#    #+#             */
/*   Updated: 2021/10/26 21:26:56 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_echo(char **arg)
{
    int i = 1;


    if (ft_strncmp(arg[i], "-n", 2) == 0)
    {
        i++;
        while (arg[i] != NULL)
        {
            ft_putstr_fd(arg[i], 1);
            write(1, " ", 1);
            i++;
        }
        return 1;       
    }
    else
    {
        while (arg[i] != NULL)
        {
            ft_putstr_fd(arg[i], 1);
            write(1, " ", 1);
            i++;
        }
        ft_putstr_fd("\n", 1);
        return 1;
    }
    ft_putstr_fd("\n", 1);
    return 0;
}