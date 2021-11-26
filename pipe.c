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
		c_tmp = substitute_env_var(com, tab[i]);
		if (tab[i] != NULL)
			free(tab[i]);
		tab[i] = c_tmp;
		ft_delete_quotes(tab[i]);
		i++;
	}
	return (tab);
}

int execute_cmd(t_command com, char **env, int last_child_status)
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
		{
			ft_read_from_shell(com, 0);
			if (ft_infile(com, 0) < 0 || ft_outfile(com, 0) < 0 || ft_outfile_append(com, 0) < 0)
				exit(EXIT_FAILURE);
		}
	}
	arg = create_tab(com);
	if (ft_strncmp(arg[0], "pwd", ft_strlen(arg[0])) == 0 && ft_strlen("pwd") == ft_strlen(arg[0]))
		ret = ft_pwd();
	else if (ft_strncmp(arg[0], "cd", ft_strlen(arg[0])) == 0 && ft_strlen("cd") == ft_strlen(arg[0]))
		ret = ft_cd(arg);
	else if (ft_strncmp(arg[0], "echo", ft_strlen(arg[0])) == 0 && ft_strlen("echo") == ft_strlen(arg[0]))
		ret = ft_echo(arg);
	else if (ft_strncmp(arg[0], "env", ft_strlen(arg[0])) == 0 && ft_strlen("env") == ft_strlen(arg[0]))
		ret = ft_env(com.env);
	else if (ft_strncmp(arg[0], "export", ft_strlen(arg[0])) == 0 && ft_strlen("export") == ft_strlen(arg[0]))
		ret = ft_export(com.env, arg);
	else if (ft_strncmp(arg[0], "unset", ft_strlen(arg[0])) == 0 && ft_strlen("unset") == ft_strlen(arg[0]))
		ret = ft_unset(&com.env, arg);
	else
	{
		full_cmd = find_cmd_path(arg[0]);
		if (full_cmd != NULL)
		{
			arg[0] = full_cmd;
			tab = convert_list_to_tab(com.env);
			ret = execve(arg[0], arg, tab); // replace en by list
		}
		else
		{
			if ( arg[0][0] == '?')
				printf("minishell: command not found : %d%s\n", WEXITSTATUS(last_child_status), arg[0] + 1);
			else
				printf("minishell: command not found : %s\n", arg[0]);
			ret = -1;
		}
	}
	free(arg);
	return ret;
}

int pipe_cmd(t_command com, int is_previous, int is_coming, int *old_pipe[], int last_child_status, char **env, int execute)
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
		ft_read_from_shell(com, 1);
		if (ft_infile(com, 1) < 0)
			exit(EXIT_FAILURE);
		if(com.in_file_num > 0)
			is_previous = 1;
		if (is_previous) // if there is a previous command
		{
			dup2(*old_pipe[0], 0);
			close(*old_pipe[0]);
			close(*old_pipe[1]);
		}
		if (ft_outfile(com, 1) < 0 || ft_outfile_append(com, 1) < 0)
			exit(EXIT_FAILURE);
		if (is_coming && com.out_file_num == 0 && com.out_file_app_num == 0) // if there is a coming command
		{
			close(new_pipe[0]);
			dup2(new_pipe[1], 1);
			close(new_pipe[1]);
		}
		if(execute && ft_strlen(com.com) > 0)
		{
			if (execute_cmd(com, env, last_child_status) < 0)
				exit(EXIT_FAILURE);
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
	return child_status;
}