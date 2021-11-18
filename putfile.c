/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:51:09 by ybesbes           #+#    #+#             */
/*   Updated: 2021/11/18 14:51:13 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_infile(t_command com)
{
	int i;
	int fd;

	i = 0;
	if (com.inputfiles != NULL)
	{
		while(com.inputfiles[i] != NULL)
		{
			fd = open(com.inputfiles[i], O_RDONLY);
			if ( fd < 0)
			{
				perror("minishell");
				return (fd);
			}
			dup2(fd , STDIN_FILENO);
			close(fd);
			i++;
		}
	}
	return (0);
}

int ft_outfile(t_command com)
{
	int i;
	int fd;

	i = 0;
	if (com.outputfiles != NULL)
	{
		while (com.outputfiles[i] != NULL)
		{
			fd = open(com.outputfiles[i], O_RDWR | O_TRUNC | O_CREAT , 0644);
			if ( fd < 0)
			{
				perror("minishell");
				return (fd);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
			i++;
		}
	}
	return (0);
}

int ft_outfile_append(t_command com)
{
	int i;
	int fd;

	i = 0;
	if (com.output_files_append != NULL)
	{
		while (com.output_files_append[i] != NULL)
		{
			fd = open(com.output_files_append[i], O_RDWR | O_CREAT | O_APPEND , 0644);
			if ( fd < 0)
			{
				perror("minishell");
				return fd;
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
			i++;
		}
	}
	return (0);
}