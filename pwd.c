/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:40:43 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/28 12:13:16 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*str;
	char	*buf;

	buf = NULL;
	str = getcwd(buf, 0);
	ft_putstr_fd(str, 1);
	if (buf != NULL)
		free(buf);
	if (str != NULL)
		free(str);
	ft_putstr_fd("\n", 1);
	return (0);
}
