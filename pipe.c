/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 10:09:57 by ybesbes           #+#    #+#             */
/*   Updated: 2021/11/25 14:09:02 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **create_tab(t_command com)
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
		if (com.args[i] == '\"' && (i == 0 || com.args[i - 1] != '\\'))
		{
			tmp = i;
			i++;
			while (com.args[i] != '\0' && (com.args[i] != '\"' || com.args[i - 1] == '\\'))
				i++;
			tab[j] = ft_substr(com.args, tmp, i - tmp + 1);
			j++;
		}
		else if (com.args[i] == '\'')
		{
			tmp = i;
			i++;
			while (com.args[i] != '\0' && com.args[i] != '\'')
				i++;
			tab[j] = ft_substr(com.args, tmp, i - tmp + 1);
			j++;
		}
		else if (ft_isspace(com.args[i]) == 0)
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
		c_tmp = substitute_env_var(tab[i]);
		if (tab[i] != NULL)
			free(tab[i]);

		tab[i] = c_tmp;
		ft_delete_quotes(tab[i]);
		i++;
	}
	return (tab);
}

int ft_compare(char *s1, char *s2)
{
	int len1;
	int len2;
	int i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;

	if (len1 != len2 || len2 == 0)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}
int execute_cmd(t_command com, char **env, t_env **env_arr)
{
	char *str;
	char **arg;
	char *full_cmd;
	int ret;

	ret = 0;

	arg = create_tab(com);
	if (ft_compare(arg[0], "pwd"))
		ret = ft_pwd();
	else if (ft_compare(arg[0], "cd"))
		ret = ft_cd(arg);
	else if (ft_compare(arg[0], "echo"))
		ret = ft_echo(arg);
	else if (ft_compare(arg[0], "env"))
		ret = ft_env(*env_arr);
	else if (ft_compare(arg[0], "export"))
		ret = ft_export(*env_arr, arg);
	else if (ft_compare(arg[0], "unset"))
		ret = ft_unset(env_arr, arg);
	else
	{
		full_cmd = find_cmd_path(arg[0]);
		if (full_cmd != NULL)
		{
			arg[0] = full_cmd;
			execve(arg[0], arg, env);// todo use env_arr instead of env
		}
		else
		{
			printf("minishell: command not found : %s\n", arg[0]);
			ret = -1;
		}
	}
	free(arg);
	return ret; // todo
}

int pipe_cmd(t_command com, int is_previous, int is_coming, int *old_pipe[], int last_child_status, char **env, int execute, t_env **env_arr)
{
	int i;
	int new_pipe[2];
	int child_status;

	char **com_tab;
	pid_t cpid;
	pid_t tpid;
	i = 0;
	ft_memset(new_pipe, 0x00, sizeof(new_pipe));

	if (is_coming)
		pipe(new_pipe);
	cpid = fork();
	if (cpid == 0) // child
	{

		if (is_previous) // if there is a previous command
		{
			dup2(*old_pipe[0], 0);
			close(*old_pipe[0]);
			close(*old_pipe[1]);
		}
		if (is_coming && com.out_file_num == 0 && com.out_file_app_num == 0) // if there is a coming command
		{
			close(new_pipe[0]);
			dup2(new_pipe[1], 1);
			close(new_pipe[1]);
		}
		ft_read_from_shell(com);
		if (ft_infile(com) < 0 || ft_outfile(com) < 0 || ft_outfile_append(com) < 0)
			exit(EXIT_FAILURE);
		if(execute)
		{
			if (execute_cmd(com, env, env_arr) < 0)
			{
				exit(EXIT_FAILURE);
			}
		}
		exit(EXIT_SUCCESS);
	}
	else if (cpid > 0) // parent
	{
		if (is_previous) // previous command
		{
			close(*old_pipe[0]);
			close(*old_pipe[1]);
		}
		if (is_coming) // comming command
		{
			*old_pipe[0] = new_pipe[0];
			*old_pipe[1] = new_pipe[1];
		}
	}
	else
	{
		perror("creating fork failed");
		return (-1);
	}
	waitpid(cpid, &child_status, 0);
	while (com.args[i] != '\0')
	{
		if (com.args[i] == '$' && com.args[i + 1] != '\0' && com.args[i + 1] == '?')
			printf("$? = %d\n", WEXITSTATUS(last_child_status));
		i++;
	}
	return child_status;
}