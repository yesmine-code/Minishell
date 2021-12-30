/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 20:12:20 by mrahmani          #+#    #+#             */
/*   Updated: 2021/12/15 20:12:28 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	is_char(char *com, int *i, int *j, char **tab)
{
	int	tmp;

	tmp = *i;
	while (com[*i] != '\0' && (ft_isspace(com[*i]) == 0
			|| is_it_between_quotes(com, *i) == 1))
		*i += 1;
	tab[*j] = ft_substr(com, tmp, *i - tmp);
	*j += 1;
}

char	**create_tab(t_command com, t_shellinfo shell)
{
	char	**tab;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = substitute_env_var(shell, com.args);
	if (tmp == NULL)
		return (NULL);
	tab = malloc(sizeof(char *) * (space_calcul(tmp) + 2));
	if (tab == NULL)
		return (NULL);
	while (tmp[i] != '\0')
	{
		if (ft_isspace(tmp[i]) == 0)
			is_char(tmp, &i, &j, tab);
		else
			i++;
	}
	tab[j] = NULL;
	ft_delete_qt(tab);
	free(tmp);
	return (tab);
}

int	com_belong_in_paths(char **paths, char *com)
{
	int		i;
	char	*tmp;

	i = (int)ft_strlen(com);
	while (i > 0 && com[i] != '/')
		i--;
	if (i == 0)
		return (0);
	tmp = ft_substr(com, 0, i);
	i = 0;
	while (paths[i] != NULL)
	{
		if (ft_strcompare(paths[i], tmp) == 1)
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

char	*join_with_slash(char **path_tab, char *cmd, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = ft_strjoin(path_tab[*i], "/");
	tmp = ft_strjoin(tmp2, cmd);
	free(tmp2);
	return (tmp);
}
