/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:59:29 by ybesbes           #+#    #+#             */
/*   Updated: 2021/09/28 14:59:33 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit(t_shellinfo shell, int stat)
{
	if (shell.old_pipe[0] != NULL)
		free(shell.old_pipe[0]);
	if (shell.old_pipe[1] != NULL)
		free(shell.old_pipe[1]);
	free_env_list(shell.env);
	if (stat == 0)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}
