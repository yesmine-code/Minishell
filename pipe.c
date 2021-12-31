/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 10:09:57 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/30 22:31:13 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	old_pipe_set(t_shellinfo *shell, char **commands)
{
	shell->old_pipe[0] = malloc(sizeof(int));
	if (shell->old_pipe[0] == NULL)
		ft_exit(NULL, *shell, 0, commands);
	ft_memset(shell->old_pipe[0], 0, sizeof(int));
	shell->old_pipe[1] = malloc(sizeof(int));
	if (shell->old_pipe[1] == NULL)
		ft_exit(NULL, *shell, 0, commands);
	ft_memset(shell->old_pipe[1], 0, sizeof(int));
	shell->previous = 0;
}

int	ft_envsize(t_env *env)
{
	int	i;

	i = 0;
	while (env && env->var)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**convert_list_to_tab(t_env *env)
{
	char	**tab;
	int		tablen;
	int		i;

	i = 0;
	tablen = ft_envsize(env);
	tab = malloc(sizeof(char *) * (tablen + 1));
	while (env && env->var)
	{
		tab[i] = env->var;
		i++;
		env = env->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	execute_cmd(t_command com, t_shellinfo shell, char **commands)
{
	char	**arg;
	int		ret;

	ret = 0;
	ret = check_for_files(shell, com);
	arg = create_tab(com, shell);
	if (ft_strcompare(arg[0], "exit") == 1)
		exit_minishell(com, arg, shell, commands);
	else if (ft_strcompare(arg[0], "pwd") == 1)
		ret = ft_pwd();
	else if (ft_strcompare(arg[0], "cd") == 1)
		ret = ft_cd(arg);
	else if (ft_strcompare(arg[0], "echo") == 1)
		ret = ft_echo(arg);
	else if (ft_strcompare(arg[0], "env") == 1)
		ret = ft_env(shell.env, arg);
	else if (ft_strcompare(arg[0], "export") == 1)
		ret = ft_export(shell.env, arg);
	else if (ft_strcompare(arg[0], "unset") == 1)
		ret = ft_unset(&shell.env, arg);
	else
		ret = find_and_execute(shell, arg);
	ft_free_tab(arg);
	return (ret);
}

pid_t	pipe_cmd(t_command com, t_shellinfo shell)
{
	int		new_pipe[2];
	pid_t	cpid;

	ft_memset(new_pipe, 0x00, sizeof(new_pipe));
	if (shell.coming)
	{
		if (pipe(new_pipe) < 0)
			exit(EXIT_FAILURE);
	}
	if (ft_strcompare(com.com, "./minishell") == 1)
	{
		signal(SIGINT, SIG_IGN);
	}
	if (com.read_from_shell != NULL)
		signal(SIGQUIT, SIG_IGN);
	cpid = fork();
	if (cpid < 0)
	{
		perror("creating fork failed");
		g_shell_status = -1;
		exit(EXIT_FAILURE);
	}
	else if (cpid == 0)
	{		
		signal(SIGINT, SIG_DFL);
		//signal(SIGQUIT, SIG_DFL);
		if (com.read_from_shell != NULL)	
		{	
			signal(SIGQUIT, SIG_IGN);
		}
		case_of_0_cpid(com, shell, new_pipe);
	}
	else
		case_of_positive_cpid(cpid, shell, new_pipe);
	return (cpid);
}
