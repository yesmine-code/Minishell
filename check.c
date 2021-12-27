/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:33:55 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/25 21:51:54 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *str, int *i, int *single_quotes, int *double_quotes)
{
	while (str != NULL && str[*i] != '\0')
	{
		if (str[*i] == '\"' && (*i == 0 || str[*i - 1] != '\\'))
		{
			*double_quotes += 1;
			*i += 1;
			while (str[*i] != '\0' && (str[*i] != '\"' || str[*i - 1] == '\\'))
					*i += 1;
			if (str[*i] == '\0')
				return (1);
			*double_quotes += 1;
		}
		if (str[*i] == '\'' && (*i == 0 || str[*i - 1] != '\\'))
		{
			*single_quotes += 1;
			*i += 1;
			while (str[*i] != '\0' && (str[*i] != '\'' || str[*i - 1] == '\\'))
				*i += 1;
			if (str[*i] == '\0')
				return (1);
			*single_quotes += 1;
		}
		*i += 1;
	}
	return (0);
}

int	check_inclosed_quotes(char *str)
{
	int		i;
	int		quotes_num;
	int		double_quotes_num;

	i = 0;
	double_quotes_num = 0;
	quotes_num = 0;
	if (check_quotes(str, &i, &quotes_num, &double_quotes_num) == 1)
		return (1);
	if (quotes_num % 2 != 0 || double_quotes_num % 2 != 0)
		return (1);
	return (0);
}

int	check_syntax_errors(char *str)
{
	int		i;

	i = ft_strlen(str);
	if (check_inclosed_quotes(str) == 1)
		return (1);
	if (str != NULL && str[0] == '|')
		return (1);
	if (str != NULL && i > 0 && (str[i - 1] == '|'
			|| str[i - 1] == '<' || str[i - 1] == '>'))
		return (1);
	return (0);
}

char	*read_check_and_trim(t_shellinfo shell)
{
	char	*str;
	char	*tmp;

	str = readline("minishell->");
	add_history(str);
	if (str == NULL)
	{
		printf("\n");
		ft_exit(NULL, shell, 0, NULL);
	}
	tmp = ft_strtrim(str, " \t\r\f\v\n");
	free(str);
	if (check_syntax_errors(tmp) == 1)
	{
		printf("error : syntax_error\n");
		free(tmp);
		tmp = NULL;
	}
	return (tmp);
}
