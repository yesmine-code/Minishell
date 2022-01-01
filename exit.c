/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:59:29 by ybesbes           #+#    #+#             */
/*   Updated: 2022/01/01 12:29:43 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	arg_is_digit(char *arg)
{
	int		i;

	i = 0;
	if (arg == NULL)
		return (0);
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	get_status(char **arg)
{
	int	stat;

	stat = g_shell_status;
	if (arg[1] == NULL)
		printf ("exit\n");
	else if (arg_is_digit(arg[1]) == 0)
	{
		printf("exit\n");
		printf("exit: %s:  numeric argument required\n", arg[1]);
		stat = 2;
	}
	else if (arg_is_digit(arg[1]) == 1)
	{
		printf("exit\n");
		stat = ft_atoi(arg[1]);
	}
	return (stat);
}

int	exit_minishell(t_command com, char **arg,
		t_shellinfo shell, char **commands)
{
	int	stat;

	if (arg[2] != NULL && arg_is_digit(arg[1]) == 1)
	{
		printf("exit\n");
		printf("exit: too many arguments\n");
		if (g_shell_status == 0)
			g_shell_status = 1;
		return (g_shell_status);
	}
	stat = get_status(arg);
	ft_free_cmd(&com);
	ft_exit(arg, shell, stat, commands);
	return (stat);
}

void	ft_exit(char **arg, t_shellinfo shell, int stat, char **commands)
{
	ft_free_tab(arg);
	ft_free_tab(commands);
	ft_free_old_pipe(shell);
	free_env_list(shell.env);
	exit(stat);
}
