/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:24:03 by mrahmani          #+#    #+#             */
/*   Updated: 2021/12/15 21:15:29 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_it_between_simple_quotes(char *str, int pos)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (i < pos)
	{
		if (str[i] == '\'')
			result++;
		i++;
	}
	if (result % 2 != 0)
		return (1);
	return (0);
}

void	double_qtes_enum(char *str, int *i, int *result1)
{
	if (str[*i] == '\"' && (*i == 0 || str[*i - 1] != '\\'))
	{
		*result1 = *result1 + 1;
		while ((str[*i] != '\"' || str[*i - 1] == '\\') && str[*i] != '\0')
			*i = *i + 1;
	}
}

int	is_it_between_quotes(char *str, int pos)
{
	int	i;
	int	result;
	int	result1;

	i = 0;
	result = 0;
	result1 = 0;
	while (i < pos)
	{
		double_qtes_enum(str, &i, &result1);
		if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
		{
			result++;
			while ((str[i] != '\'' || str[i - 1] == '\\') && str[i] != '\0')
				i++;
		}
		i++;
	}
	if (result % 2 != 0 || result1 % 2 != 0)
		return (1);
	return (0);
}
