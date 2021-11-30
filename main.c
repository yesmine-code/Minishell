/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 10:46:30 by ybesbes           #+#    #+#             */
/*   Updated: 2021/10/31 17:04:34 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int g_shell_status;

int main(int ac, char **av, char **env)
{
	char *str;
	char *tmp;
	char **commands;
	t_shellinfo shell;
	t_command com_struct;
	int i;

	if (ac > 1)
	{
		printf("ERROR :this program doesn't work with arguments\n");
		exit(EXIT_FAILURE);
	}
	av[1] = NULL;
	shell.env = NULL;
	shell.previous = malloc(sizeof(int));
	if (shell.previous == NULL)
		exit(EXIT_FAILURE);
	g_shell_status = 0;
	handle_ctrl_c();
	handle_ctrl_backslash();
	while (1)
	{
		i = 0;
		str = readline("minishell->");
		add_history(str);
		if (str == NULL)
		{
			printf("\n");
			exit(EXIT_SUCCESS);// ctrl_d
		}
		tmp = ft_strtrim(str, " \t\r\f\v\n");
		free(str);
		if (ft_strcompare(tmp, "exit") == 1) 
		{
			free(tmp);
			exit(EXIT_SUCCESS);
		}
		if (check_syntax_errors(tmp) == 1)
		{
			printf("error : syntax_error\n");
			free(tmp);
		}
		else
		{
			commands = ft_mini_split(tmp, '|');
			shell.old_pipe[0] = malloc(sizeof(int));
			shell.old_pipe[1] = malloc(sizeof(int));
			ft_memset(*(shell.old_pipe), 0x00, sizeof(*(shell.old_pipe)));
			*shell.previous = 0;
			while (commands[i] != NULL)
			{
				shell.coming = (commands[i + 1] == NULL) ? 0 : 1;
				com_struct = get_cmd(commands[i]);
				init_env(&shell.env, env);
				if(is_a_real_builtin(com_struct.com) == 0)
				{
					shell.execute = 1;
					pipe_cmd(com_struct, shell);
				}
				else if (i == 0 && commands[i + 1] == NULL)
				{
					if (execute_cmd(com_struct, shell) < 0)
						break ;
				}
				else
				{
					shell.execute = 0;
					pipe_cmd(com_struct, shell);
				}
				i++;
				*shell.previous = 1;
				ft_free_cmd(&com_struct);
				if (g_shell_status != 0)
					break ;
			}
			if(is_builtin(com_struct.com) == 0)
			{
				free(shell.old_pipe[0]);
				free(shell.old_pipe[1]);
			}
		}
	}
	return (g_shell_status);
}

