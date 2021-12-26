/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putfile2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 14:30:16 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/26 14:30:18 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	ft_infile(t_command com, int dupit)
{
	int	i;
	int	fd;

	i = 0;
	if (com.inputfiles != NULL)
	{
		while (com.inputfiles[i] != NULL)
		{
			fd = open(com.inputfiles[i], O_RDONLY);
			if (fd < 0)
			{
				perror("minishell");
				return (fd);
			}
			if (dupit == 1)
			{
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			i++;
		}
	}
	return (0);
}

int	ft_outfile(t_command com, int dupit)
{
	int	i;
	int	fd;

	i = 0;
	if (com.outputfiles != NULL)
	{
		while (com.outputfiles[i] != NULL)
		{
			fd = open(com.outputfiles[i], O_RDWR | O_TRUNC | O_CREAT, 0644);
			if (fd < 0)
			{
				perror("minishell");
				return (fd);
			}
			if (dupit == 1)
			{
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
			i++;
		}
	}
	return (0);
}
