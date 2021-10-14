/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:20:08 by ybesbes           #+#    #+#             */
/*   Updated: 2021/10/14 15:20:14 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_cmd(t_command *com)
{
	if (com->com != NULL)
		free (com->com);
	if (com->args != NULL)
		free (com->args);
	if (com->inputfiles != NULL)
		free (com->inputfiles);
	if (com->output_files_append != NULL)
		free (com->output_files_append);
	if (com->read_from_shell != NULL)
		free (com->read_from_shell);
}