/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 10:46:30 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/26 18:02:50 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int		g_shell_status;

pid_t	executer(t_command com_struct, t_shellinfo shell
			, int i, char **commands)
{
	int	ret;

	ret = 0;
	if (is_a_real_builtin(com_struct.com) == 0)
	{
		shell.execute = 1;
		return (pipe_cmd(com_struct, shell));
	}
	else if (i == 0 && commands[i + 1] == NULL)
	{
		ret = execute_cmd(com_struct, shell, commands);
		g_shell_status = ret;
	}
	else
	{
		shell.execute = 0;
		return (pipe_cmd(com_struct, shell));
	}
	return (ret);
}

void	wait_for_childs(int i, int pids)
{
	while (i > 0)
	{
		waitpid(pids, &g_shell_status, 0);
		pids--;
		i--;
	}
}

void	init_com_struct(t_shellinfo *shell, char **commands)
{
	t_command		com_struct;
	struct termios	term;
	int				i;
	pid_t			pids;

	i = 0;
	tcgetattr(fileno(stdin), &term);
	while (commands && commands[i] != NULL)
	{
		if (commands[i + 1] == NULL)
			shell->coming = 0;
		else
			shell->coming = 1;
		com_struct = get_cmd(commands[i]);
		pids = executer(com_struct, *shell, i, commands);
		i++;
		shell->previous = 1;
		ft_free_cmd(&com_struct);
	}
	wait_for_childs(i, pids);
	tcsetattr(fileno(stdin), TCSAFLUSH, &term);
}

void	minishell_loop(char **env)
{
	char		**commands;
	t_shellinfo	shell;
	char		*tmp;

	init_env(&shell, env);
	while (1)
	{
		shell.old_pipe[0] = NULL;
		shell.old_pipe[1] = NULL;
		tmp = read_check_and_trim(shell);
		if (tmp == NULL)
			continue ;
		commands = ft_mini_split(tmp, '|');
		free(tmp);
		old_pipe_set(&shell, commands);
		init_com_struct(&shell, commands);
		ft_free_tab(commands);
		ft_free_old_pipe(shell);
	}
}

int	main(int ac, char **av, char **env)
{
	if (ac > 1)
	{
		printf("ERROR :this program doesn't work with arguments\n");
		exit(EXIT_FAILURE);
	}
	av[1] = NULL;
	g_shell_status = 0;
	handle_ctrl_c();
	handle_ctrl_backslash();
	minishell_loop(env);
	return (g_shell_status);
}
