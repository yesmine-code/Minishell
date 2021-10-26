/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:37:26 by mrahmani          #+#    #+#             */
/*   Updated: 2021/10/26 19:21:37 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#include "minishell.h"

int ft_cd(char *dir)
{
    DIR* d;
    errno = 0;
    d = opendir(dir);
    if(d == NULL)
    {
        perror("cd ");
        return (-1);
    }
    return chdir(dir);
}