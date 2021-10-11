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

int execute_cmd(char **cmd)
{
	char* env[] = { NULL }; //todo
	char *str;

	str = ft_strtrim(*cmd, " \t\r\f\v\n");
	if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
	{
		ft_pwd();
	}
	else
	{
		execve(*cmd, cmd , env);
	}
	return 0; //todo
}


int pipe_cmd(char **commands)
{
	int i;
	int old_pipe[2];
	int new_pipe[2];
	int child_status;

	char **com_tab;
	pid_t cpid;
	pid_t tpid;
	i = 0;
	ft_memset(old_pipe, 0x00, sizeof(old_pipe));
	ft_memset(new_pipe, 0x00, sizeof(new_pipe));
	while (commands[i] != NULL)
	{
		com_tab = split_cmd(commands[i]);

		if (commands[i + 1] != NULL)
			pipe(new_pipe);
		cpid = fork();  
		if(cpid == 0) //child
		{
			if (i > 0 && commands[i - 1] != NULL) // if there is a previous command
			{
				dup2(old_pipe[0], 0);
				close(old_pipe[0]);
				close(old_pipe[1]);
			}
			if (commands[i + 1] != NULL) // if there is a coming command
			{
				close(new_pipe[0]);
				dup2(new_pipe[1], 1);
				close(new_pipe[1]);
			}
			execute_cmd(com_tab);
			exit(EXIT_SUCCESS);
		}
		else if (cpid > 0) //parent
		{
			if (i > 0 && commands[i - 1] != NULL) //previous command
			{
				close(old_pipe[0]);
				close(old_pipe[1]);
			}
			if (commands[i + 1] != NULL) //comming command
			{
				old_pipe[0] = new_pipe[0];
				old_pipe[1] = new_pipe[1];
			}
		}
		else
		{
			perror("creating fork failed");
			return (-1);
		}
		waitpid(cpid, &child_status, 0);
		i++;
	}
	return 0;
}