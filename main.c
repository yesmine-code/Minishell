/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 10:46:30 by ybesbes           #+#    #+#             */
/*   Updated: 2021/11/19 00:23:22 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void print_cmd(t_command com)
{
	int i = 0;
	printf("command : %s\n", com.com);
	printf("args : %s\n", com.args);
	printf("outputfiles: ");
	while (com.outputfiles != NULL && i < com.out_file_num)
	{
		printf("%s--", com.outputfiles[i]);
		i++;
	}
	printf("\ninputfiles: ");
	i = 0;
	while (com.inputfiles != NULL && i < com.in_file_num)
	{
		printf("%s\t", com.inputfiles[i]);
		i++;
	}
	printf("\noutputfiles_app: ");
	i = 0;
	while (com.output_files_append != NULL && i < com.out_file_app_num)
	{
		printf("%s\t", com.output_files_append[i]);
		i++;
	}
	printf("\nread_from_shell: ");
	i = 0;
	while (com.read_from_shell != NULL && i < com.expected_words_num)
	{
		printf("%s\t", com.read_from_shell[i]);
		i++;
	}
	printf("\n----------------\n");
}

int main(int ac, char **av, char **env)
{
	char *str;
	char *tmp;
	char **commands;
	t_command com_struct;
	t_env *env_list;

	env_list = NULL;
	init_env(&env_list, env);
	int last_child_status;
	int child_status;
	int i;

	last_child_status = 0;
	child_status = 0;
	handle_ctrl_c();
	while (1)
	{
		i = 0;
		str = readline("minishell->");
		if (str == NULL)
		{
			printf("\n");
			exit(EXIT_SUCCESS); // ctrl_d
		}
		add_history(str);
		tmp = ft_strtrim(str, " \t\r\f\v\n");
		free(str);
		if (ft_strncmp(tmp, "exit", ft_strlen(tmp)) == 0 && ft_strlen(tmp) == ft_strlen("exit"))
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

			int *old_pipe[2];

			old_pipe[0] = malloc(sizeof(int));
			old_pipe[1] = malloc(sizeof(int));
			ft_memset(*old_pipe, 0x00, sizeof(*old_pipe));

			int previous;
			int coming;

			previous = 0;
			while (commands[i] != NULL)
			{
				coming = (commands[i + 1] == NULL) ? 0 : 1;
				com_struct = get_cmd(commands[i], env);
				//	print_cmd(com_struct);
				if(is_a_real_builtin(com_struct.com) == 1)
				{
					child_status = pipe_cmd(com_struct, previous, coming, old_pipe, last_child_status, env, 1, &env_list);
				}
				else if (i == 0 && commands[i + 1] == NULL)
					execute_cmd(com_struct, env, &env_list);
				else
					child_status = pipe_cmd(com_struct, previous, coming, old_pipe, last_child_status, env, 0, &env_list);
				i++;
				previous = 1;
				ft_free_cmd(&com_struct);
			}
			last_child_status = child_status;
			if(is_builtin(com_struct.com) == 0)
			{
				free(old_pipe[0]);
				free(old_pipe[1]);
			}
			
		}
	}
}

