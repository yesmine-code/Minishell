/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:37:26 by mrahmani          #+#    #+#             */
/*   Updated: 2021/10/27 20:52:18 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#include "minishell.h"

int ft_cd(char **arg)
{
    DIR* d;
    errno = 0;

    if (arg[1] == NULL)
        return (-1);
    d = opendir(arg[1]);
    if(d == NULL)
    {
        perror("cd ");
        return (-1);
    }
    
    return chdir(arg[1]);
}