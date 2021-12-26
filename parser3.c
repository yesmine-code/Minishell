/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:19:24 by mrahmani          #+#    #+#             */
/*   Updated: 2021/12/26 22:30:54 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_chars(int *pos, int back_slash_nb, char *com)
{
	int	i;

	i = back_slash_nb - 1;
	while (i >= 0)
	{
		ft_remove_char(com, pos[i]);
		i--;
	}
}

void	create_postab(char *com, int back_slash_nb)
{
	int	*pos;
	int	i;
	int	j;

	j = 0;
	i = 0;
	pos = malloc(sizeof(int) * (back_slash_nb + 1));
	if (pos != NULL)
	{
		while (com[i] != '\0')
		{
			if (com[i] == '\\' && com[i + 1] != '\0'
				&& (com[i + 1] == '\'' || com[i + 1] == '\"' ))
			{
				pos[j] = i;
				j++;
			}
			i++;
		}
		pos[j] = '\0';
		remove_chars(pos, back_slash_nb, com);
		free(pos);
	}
}

void	ft_delete_backslash(char *com)
{
	int	i;
	int	back_slash_nb;

	i = 0;
	back_slash_nb = 0;
	while (com[i] != '\0')
	{
		if (com[i] == '\\' && com[i + 1] != '\0' && (com[i + 1] == '\''
				|| com[i + 1] == '\"' ))
		back_slash_nb++;
		i++;
	}
	create_postab(com, back_slash_nb);
}
