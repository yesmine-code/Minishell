/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 10:46:30 by ybesbes           #+#    #+#             */
/*   Updated: 2021/09/27 10:46:33 by ybesbes          ###   ########.fr       */
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

int main(void)
{
	char *str;
	char *tmp;
	char **commands;
	t_command com_struct;
	int i;

	while (1)
	{
		i = 0;
		str = readline("minishell->");
		add_history(str);
		tmp = ft_strtrim(str, " \t\r\f\v\n");
		free(str);
		if (ft_strncmp(tmp, "exit", ft_strlen(tmp)) == 0)
		{
			free(tmp);
			exit (EXIT_SUCCESS);			
		}
		if (check_syntax_errors(tmp) == 1)
		{
			printf("error : syntax_error\n");
			free(tmp);
		}
		else
		{
			commands = ft_split(tmp, '|');
			int previous;
			int coming;

			while (commands[i] != NULL)
			{
				previous = (i == 0) ? 0 : 1;
				coming = (commands[i + 1] == NULL) ? 0 : 1;
				com_struct = get_cmd(commands[i]);
			//	print_cmd(com_struct);
				pipe_cmd(com_struct, previous, coming);
				ft_free_cmd(&com_struct);
				i++;
			}
			
		}
	}

}

