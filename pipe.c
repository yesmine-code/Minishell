/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 10:09:57 by ybesbes           #+#    #+#             */
/*   Updated: 2021/10/31 17:13:59 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_shell_status;

int	ft_envsize(t_env *env)
{
	int i;

	i = 0;
	while (env && env->var)
	{
		i++;
		env = env->next;
	}
	return i;
}
char **convert_list_to_tab(t_env *env)
{
	char **tab;
	int	 tablen;
	int i;

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


char **create_tab(t_command com, t_shellinfo shell)
{
	char **tab;
	int i;
	int j;
	int tmp;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * (char_numb(com.args, ' ', 0) + 2));
	while (com.args[i] != '\0')
	{
		if (com.args[i] == '\"' && (i == 0 || com.args[i - 1] != '\\')) //si double cote
		{
			tmp = i;
			i++;
			while (com.args[i] != '\0' && (com.args[i] != '\"' || com.args[i - 1] == '\\'))
				i++;
			tab[j] = ft_substr(com.args, tmp, i - tmp + 1);
			j++;
			i++;
		}
		else if (com.args[i] == '\'') // si cote
		{
			tmp = i;
			i++;
			while (com.args[i] != '\0' && com.args[i] != '\'')
				i++;
			tab[j] = ft_substr(com.args, tmp, i - tmp + 1);
			j++;
			i++;
		}
		else if (ft_isspace(com.args[i]) == 0) //si caractere
		{
			tmp = i;
			while (ft_isspace(com.args[i]) == 0 && com.args[i] != '\0' || is_it_between_quotes(com.args, i) == 1)
				i++;
			tab[j] = ft_substr(com.args, tmp, i - tmp);
			j++;
		}
		else
			i++;
	}
	tab[j] = NULL;
	i = 0;
	char *c_tmp;
	while (tab[i] != NULL)
	{
		c_tmp = substitute_env_var(shell, tab[i]);
		if (tab[i] != NULL)
			free(tab[i]);
		tab[i] = c_tmp;
		ft_delete_quotes(tab[i]);
		i++;
	}
	return (tab);
}

int execute_cmd(t_command com, char **env, t_shellinfo shell)
{
	char *str;
	char **arg;
	char *full_cmd;
	int ret;
	char **tab;
	pid_t cpid;

	ret = 0;
	if(is_a_real_builtin(com.com) == 1)
	{
		ft_read_from_shell(com, 0);
		if (ft_infile(com, 0) < 0 || ft_outfile(com, 0) < 0 || ft_outfile_append(com, 0) < 0)
			exit(EXIT_FAILURE);
	}
	arg = create_tab(com, shell);
	if (ft_strcompare(arg[0], "pwd") == 1)
		ret = ft_pwd();
	else if (ft_strcompare(arg[0], "cd") == 1)
		ret = ft_cd(arg);
	else if (ft_strcompare(arg[0], "echo") == 1)
		ret = ft_echo(arg);
	else if (ft_strcompare(arg[0], "env") == 1)
		ret = ft_env(shell.env);
	else if (ft_strcompare(arg[0], "export") == 1)
		ret = ft_export(shell.env, arg);
	else if (ft_strcompare(arg[0], "unset") == 1)
		ret = ft_unset(&shell.env, arg);
	else
	{
		full_cmd = find_cmd_path(arg[0]);
		if (full_cmd != NULL)
		{
			arg[0] = full_cmd;
			tab = convert_list_to_tab(shell.env);
			ret = execve(arg[0], arg, tab); // replace en by list
		}
		else
		{
			if ( arg[0][0] == '?')
			{
				if (g_shell_status == 130)
					printf("minishell: command not found : %d%s\n", g_shell_status, arg[0] + 1);
				else
					printf("minishell: command not found : %d%s\n", WEXITSTATUS(g_shell_status), arg[0] + 1);
			}
			else
				printf("minishell: command not found : %s\n", arg[0]);
			ret = -1;
		}
	}
	free(arg);
	return ret;
}

void pipe_cmd(t_command com, t_shellinfo shell, char **env)
{
	int i;
	int new_pipe[2];
	char **com_tab;
	pid_t cpid;
	pid_t tpid;

	i = 0;
	ft_memset(new_pipe, 0x00, sizeof(new_pipe));
	if (shell.coming)
		pipe(new_pipe);
	cpid = fork();
	if (cpid == 0) // child
	{
		ft_read_from_shell(com, 1);
		if (ft_infile(com, 1) < 0)
			exit(EXIT_FAILURE);
		if(com.in_file_num > 0)
			*shell.previous = 1;
		if (*shell.previous) // if there is a previous command
		{
			dup2(*shell.old_pipe[0], 0);
			close(*shell.old_pipe[0]);
			close(*shell.old_pipe[1]);
		}
		if (ft_outfile(com, 1) < 0 || ft_outfile_append(com, 1) < 0)
			exit(EXIT_FAILURE);
		if (shell.coming && com.out_file_num == 0 && com.out_file_app_num == 0) // if there is a coming command
		{
			close(new_pipe[0]);
			dup2(new_pipe[1], 1);
			close(new_pipe[1]);
		}
		if(shell.execute && ft_strlen(com.com) > 0)
		{
			if (execute_cmd(com, env, shell) < 0)
				exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else if (cpid > 0) // parent
	{
		if (*shell.previous) // previous command
		{
			close(*shell.old_pipe[0]);
			close(*shell.old_pipe[1]);
		}
		if (shell.coming) // comming command
		{
			*shell.old_pipe[0] = new_pipe[0];
			*shell.old_pipe[1] = new_pipe[1];
		}
	}
	else
	{
		perror("creating fork failed");
		g_shell_status = -1;
	}
	waitpid(cpid, &g_shell_status, 0);
}