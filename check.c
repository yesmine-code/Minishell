/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:33:55 by ybesbes           #+#    #+#             */
/*   Updated: 2021/09/27 15:33:59 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_errors(char *str)
{
	int i;

	i = ft_strlen(str);
	if (char_numb(str, '\'', 0) % 2 != 0)
		return (1);
	if (char_numb(str, '"', 0) % 2 != 0)
		return (1);
	if (str[0] == '|')
		return (1);
	if (str[i - 1] == '|' || str[i - 1] == '<' || str[i - 1] == '>')
		return (1);
	return (0);
}

int is_builtin(char *str)
{
	if (ft_strncmp(str, "cd", ft_strlen(str)) == 0)
		return(1);
	if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
		return(1);
	if (ft_strncmp(str, "export", ft_strlen(str)) == 0)
		return(1);
	if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
		return(1);
	if (ft_strncmp(str, "echo", ft_strlen(str)) == 0)
		return(1);
	if (ft_strncmp(str, "unset", ft_strlen(str)) == 0)
		return(1);
	return (0);
}

