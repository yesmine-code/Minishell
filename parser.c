/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 13:20:37 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/19 20:12:35 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*getenv_value_from_list(t_shellinfo shell, char *env)
{
	while (shell.env && shell.env->var)
	{
		if (ft_strcompare(shell.env->name, env) == 1)
			return (ft_strdup(shell.env->value));
		shell.env = shell.env->next;
	}
	return (ft_strdup(""));
}

char	**get_paths(t_shellinfo shell)
{
	char	*path;
	char	**path_tab;

	path = getenv_value_from_list(shell, "PATH");
	path_tab = ft_split(path, ':');
	free(path);
	return (path_tab);
}

char	*find_cmd_path(t_shellinfo shell, char *cmd)
{
	char	**path_tab;
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	path_tab = get_paths(shell);
	while (path_tab[i] != NULL)
	{
		tmp2 = ft_strjoin(path_tab[i], "/");
		tmp = ft_strjoin(tmp2, cmd);
		free(tmp2);
		if (access(tmp, F_OK) == 0)
		{
			ft_free_tab(path_tab);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	ft_free_tab(path_tab);
	return (NULL);
}

void	ft_remove_char(char *str, int pos)
{
	while (str[pos] != '\0')
	{
		str[pos] = str[pos + 1];
		pos++;
	}
}

void	remove_quotes(char *str, int *pos_tab)
{
	int	i;

	i = quotes_enum(str) - 1;
	while (i >= 0)
	{
		ft_remove_char(str, pos_tab[i]);
		i--;
	}
}
