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

void ft_read_from_shell(t_command com)
{
	int i;
	char *line;
	char *tmp;
	char *str;
	int		fds[2];

	i = 0;
	str = ft_strdup("");
	if (com.read_from_shell != NULL)
	{
		while (i < com.expected_words_num)
		{
			line = readline("heredoc>");
			if (ft_strncmp(line, com.read_from_shell[i], ft_strlen(com.read_from_shell[i])) == 0 && ft_strlen(line) == ft_strlen(com.read_from_shell[i]))
				i++;
			else
			{
				tmp = ft_strjoin(str, line);
				free(str);
				str = ft_strjoin(tmp, ft_strdup("\n"));
				free(tmp);
			}
			free(line);
		}
		tmp = ttyname(STDIN_FILENO);
		if (tmp == NULL)
			perror("minishell :");
		close(STDIN_FILENO);
		pipe(fds);
		write(fds[1], str, ft_strlen(str));
		free(str);
		close(fds[1]);
		dup2(fds[0], STDERR_FILENO);
	}
}