/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:59:29 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/16 15:47:35 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	get_status(char **arg, t_shellinfo shell, char *s, char **commands)
{
	int	i;
	int	stat;

	i = 0;
	stat = 0;
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]) == 0)
		{
			printf("exit\n");
			printf("exit: %s:  numeric argument required\n", s);
			ft_exit(arg, shell, g_shell_status, commands);
		}
		i++;
	}
	stat = ft_atoi(s);
	return (stat);
}

void	exit_minishell(t_command com, char **arg,
		t_shellinfo shell, char **commands)
{
	int	stat;

	stat = 0;
	if (arg[1] == NULL)
	{
		printf("exit\n");
		ft_free_cmd(&com);
		ft_exit(arg, shell, g_shell_status, commands);
	}
	else if (arg[2] != NULL)
	{
		printf("exit\n");
		printf("exit: too many arguments\n");
		ft_free_cmd(&com);
		ft_exit(arg, shell, g_shell_status, commands);
	}
	else
	{
		stat = get_status(arg, shell, arg[1], commands);
		printf("exit\n");
		ft_free_cmd(&com);
		ft_exit(arg, shell, stat, commands);
	}
}

void	ft_exit(char **arg, t_shellinfo shell, int stat, char **commands)
{
	ft_free_tab(arg);
	ft_free_tab(commands);
	ft_free_old_pipe(shell);
	free_env_list(shell.env);
	exit(stat);
}
