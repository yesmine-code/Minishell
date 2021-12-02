/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:20:08 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/02 22:06:33 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_tab(char **str)
{
	int i;

	i = 0;
	if (str != NULL)
	{
		while (str[i] != NULL)
		{
			free(str[i]);
			i++;
		}
		free (str);
	}
}

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

void free_env_list(t_env *env_list)
{
	t_env* next;
	while (env_list != NULL)
	{
		next = env_list->next;
		if(env_list->name != NULL)
			free(env_list->name);
		if(env_list->value != NULL)
			free(env_list->value);
		free(env_list);
		env_list = next;
	}
		
}
