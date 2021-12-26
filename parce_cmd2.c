/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_cmd2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 14:02:59 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/26 14:03:04 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_command	get_cmd(char *command)
{
	t_command	com_struct;
	char		*com_trim;

	cmd_init(command, &com_struct);
	com_trim = ft_strtrim(command, " \t\r\f\v\n");
	parse_cmd(com_trim, &com_struct);
	free(com_trim);
	return (com_struct);
}

void	ft_skip_quotes(char *str, int *i, int skip_double_q)
{
	if (skip_double_q == 1)
	{
		if (str[*i] == '\"' && (*i == 0 || str[*i - 1] != '\\'))
		{
			*i = *i + 1;
			while ((str[*i] != '\"' || str[*i - 1] == '\\') && str[*i] != '\0')
				*i = *i + 1;
		}
	}
	if (str[*i] == '\'' && (*i == 0 || str[*i - 1] != '\\'))
	{
		*i = *i + 1;
		while ((str[*i] != '\'' || str[*i - 1] == '\\') && str[*i] != '\0')
			*i = *i + 1;
	}
}

int	char_numb(char *str, char c, int two, int skip_double_q)
{
	int	i;
	int	r;
	int	rd;

	r = 0;
	rd = 0;
	i = 0;
	while (i < (int)ft_strlen(str))
	{
		ft_skip_quotes(str, &i, skip_double_q);
		if (str[i] == c)
		{
			if (str[i + 1] != c)
				r++;
			else
			{
				rd++;
				i++;
			}
		}
		i++;
	}
	if (two == 0)
		return (r);
	return (rd);
}

int	space_calcul(char *str)
{
	int	i;
	int	r;

	r = 0;
	i = 0;
	while (str[i] != '\0')
	{
		ft_skip_quotes(str, &i, 1);
		if (str[i] == ' ')
		{
			r++;
			i++;
			while (str[i] == ' ')
				i++;
		}
		else
			i++;
	}
	return (r);
}
