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
    if (ft_strncmp(arg[1], "-n", 2) == 0)
    {
        ft_putstr_fd(arg[2], 1);
        return 1;
    }
    else
    {
        ft_putstr_fd(arg[1], 1);
        ft_putstr_fd("\n", 1);
        return 1;
    }
    return 0;
}