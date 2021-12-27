/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:20:08 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/20 10:55:19 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_old_pipe(t_shellinfo shell)
{
	if (shell.old_pipe[0] != NULL)
		free(shell.old_pipe[0]);
	if (shell.old_pipe[1] != NULL)
		free(shell.old_pipe[1]);
	shell.old_pipe[0] = NULL;
	shell.old_pipe[1] = NULL;
}

void	free_env_list(t_env *env_list)
{
	t_env	*next;

	while (env_list != NULL)
	{
		next = env_list->next;
		if (env_list->value != NULL)
			free(env_list->value);
		if (env_list->name != NULL)
			free(env_list->name);
		if (env_list->var != NULL)
			free(env_list->var);
		free(env_list);
		env_list = next;
	}
}

void	ft_free_tab(char **str)
{
	int	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i] != NULL)
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

void	ft_free_cmd(t_command *com)
{
	if (com->com != NULL)
		free(com->com);
	if (com->args != NULL)
		free(com->args);
	ft_free_tab(com->inputfiles);
	ft_free_tab(com->output_files_append);
	ft_free_tab(com->read_from_shell);
	ft_free_tab(com->outputfiles);
}

void	free_str(char *s1, char *s2, char *s3, char *s4)
{
	if (s1 != NULL)
		free(s1);
	if (s2 != NULL)
		free(s2);
	if (s3 != NULL)
		free(s3);
	if (s4 != NULL)
		free(s4);
}
