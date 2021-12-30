/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:51:09 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/24 23:01:54 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_outfile_append(t_command com, int dupit)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	if (com.output_files_append != NULL)
	{
		while (com.output_files_append[i] != NULL)
		{
			fd = open(com.output_files_append[i],
					O_RDWR | O_CREAT | O_APPEND, 0644);
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

void	heredoc_helper(char *str, int dupit)
{
	char	*tmp;
	int		fds[2];

	fds[0] = 0;
	fds[1] = 0;
	tmp = ttyname(STDIN_FILENO);
	if (tmp == NULL)
		perror("minishell :");
	if (dupit == 1)
	{
		close(STDIN_FILENO);
		pipe(fds);
		write(fds[1], str, ft_strlen(str));
		close(fds[1]);
	}
}

void	get_line(char **str, char **line)
{
	char	*tmp;

	tmp = ft_strjoin(*str, *line);
	free(*str);
	*str = ft_strjoin(tmp, "\n");
	free(tmp);
}

void	ft_read_from_shell(t_shellinfo shell, t_command com, int dupit)
{
	int		i;
	char	*line;
	char	*str;
	char	*tmp;

	i = 0;
	str = ft_strdup("");
	if (com.read_from_shell != NULL)
	{
		while (i < com.expected_words_num)
		{
			line = readline("heredoc>");
			if (line == NULL)
				break ;
			tmp = substitute_env_var(shell, line);
			free(line);
			if (ft_strcompare(tmp, com.read_from_shell[i]) == 1)
				i++;
			else
				get_line(&str, &tmp);
			free(tmp);
		}
		heredoc_helper(str, dupit);
	}
	free(str);
}
