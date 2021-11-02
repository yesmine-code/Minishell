/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:37:26 by mrahmani          #+#    #+#             */
/*   Updated: 2021/10/28 15:56:20 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#include "minishell.h"

int ft_cd(char **arg)
{
    DIR *d;
    errno = 0;
    char *default_dir;
    int ret;

    if (arg[1] == NULL)
    {
        default_dir = ft_strjoin("/home/", getenv("USER"));
        ret = chdir(default_dir);
        free(default_dir);
        return (ret);
    }
    d = opendir(arg[1]);
    if (d == NULL)
    {
        perror("cd ");
        return (-1);
    }
    ret = chdir(arg[1]);
    if (ret < 0)
    {
        perror("cd ");
        return (-1);
    }
    return (ret);
}