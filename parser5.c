/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 20:09:41 by mrahmani          #+#    #+#             */
/*   Updated: 2021/12/30 11:57:36 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	caculate_char_to_add(char **str, char *com)
{
	int		i;
	int		char_to_add;

	i = 0;
	char_to_add = 0;
	while (i < char_numb(com, '$', 0, 0))
	{
		if (str[i] != NULL)
			char_to_add = char_to_add + ft_strlen(str[i]);
		i++;
	}
	return (char_to_add);
}

void	tab_init(char **str, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		str[i] = NULL;
	i++;
	}
}

char	*get_status_value(unsigned int *i)
{
	int		status;

	status = 0;
	if (WIFEXITED(g_shell_status))
		status = WEXITSTATUS(g_shell_status);
	else
		status = g_shell_status;
	*i = *i + 2;
	return (ft_itoa(status));
}

void	getenv_doll(int *char_to_extract, char *com,
		t_shellinfo shell, char **str)
{
	unsigned int	i;
	char			*env;
	int				j;
	int				tmp;

	j = 0;
	i = 0;
	while (i < ft_strlen(com))
	{
		if (com[i] == '$' && com[i + 1] != '\0' && com[i + 1] == '?')
			str[j++] = get_status_value(&i);
		else if (com[i] == '$' && is_it_between_simple_quotes(com, i) == 0)
		{
			i++;
			tmp = i;
			while ((ft_isalnum(com[i]) == 1 || com[i] == '_') && com[i] != '"' && com[i] != '\0')
				i++;
			env = ft_substr(com, tmp, i - tmp);
			*char_to_extract = *char_to_extract + ft_strlen(env) + 1;
			str[j++] = getenv_value_from_list(shell, env);
			free_str(env, NULL, NULL, NULL);
		}
		else
			i++;
	}
}

char	*substitute_env_var(t_shellinfo shell, char *com)
{
	char	**str;
	int		char_to_extract;
	int		char_to_add;
	char	*buff;

	char_to_extract = 0;
	char_to_add = 0;
	str = malloc(sizeof(char *) * (char_numb(com, '$', 0, 0) + 1));
	if (str == NULL)
		return (NULL);
	tab_init(str, char_numb(com, '$', 0, 0) + 1);
	getenv_doll(&char_to_extract, com, shell, str);
	char_to_add = caculate_char_to_add(str, com);
	buff = malloc(sizeof(char) * (ft_strlen(com)
				- char_to_extract + char_to_add + 1));
	if (buff == NULL)
		return (NULL);
	dollar_between_quotes(str, com, buff);
	ft_free_tab(str);
	return (buff);
}
