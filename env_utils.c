/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:34:36 by mrahmani          #+#    #+#             */
/*   Updated: 2021/12/26 17:35:41 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(char *s)
{
	int		i;
	int		count;
	char	*tmp;

	i = 0;
	count = 0;
	if (s != NULL)
	{
		while (s[i])
		{
			count++;
			if (s[i] == '=')
			{
				tmp = ft_substr(s, i + 1, ft_strlen(s) - count);
				return (tmp);
			}
			i++;
		}
	}
	return (ft_strdup(s));
}

char	*get_name_env(char *s)
{
	int		i;

	i = 0;
	if (s == NULL)
		return (ft_strdup(""));
	while (s[i])
	{
		if (s[i] == '=')
			return (ft_substr(s, 0, i));
		i++;
	}
	return (ft_strdup(s));
}
