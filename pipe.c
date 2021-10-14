/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 10:09:57 by ybesbes           #+#    #+#             */
/*   Updated: 2021/10/08 10:10:02 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int execute_cmd(t_command com)
{
	char* env[] = { NULL }; //todo
	char *str;
	char **arg;

	arg = ft_split(com.args, ' ');
	if (ft_strncmp(arg[0], "pwd", ft_strlen(arg[0])) == 0)
	{
		ft_pwd();
	}
	else
	{
		execve(arg[0], arg , env);
	}
	free(arg);
	return 0; //todo
}


int pipe_cmd(t_command com, int is_previous, int is_coming, int *old_pipe[])
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
	if(cpid == 0) //child
	{
		if (is_previous) // if there is a previous command
		{
			dup2(*old_pipe[0], 0);
			close(*old_pipe[0]);
			close(*old_pipe[1]);
		}
		if (is_coming) // if there is a coming command
		{
			close(new_pipe[0]);
			dup2(new_pipe[1], 1);
			close(new_pipe[1]);
		}
		execute_cmd(com);
		exit(EXIT_SUCCESS);
	}
	else if (cpid > 0) //parent
	{
		if (is_previous) //previous command
		{
			close(*old_pipe[0]);
			close(*old_pipe[1]);
		}
		if (is_coming) //comming command
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
	return 0;
}