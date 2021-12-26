/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 13:58:09 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/26 13:58:15 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	parse_cmd(char *command, t_command *com_struct)
{
	int	i;
	int	offset;

	i = 0;
	offset = 0;
	com_struct->args = malloc(sizeof(char *) * (ft_strlen(command) + 1));
	while (command[i] != '\0')
	{
		parse_single_input_redirect(command, &i, com_struct);
		parse_double_input_redirect(command, &i, com_struct);
		parse_single_output_redirect(command, &i, com_struct);
		parse_double_output_redirect(command, &i, com_struct);
		com_struct->args[offset++] = command[i];
		i++;
	}
	com_struct->args[offset] = '\0';
	if (ft_strchr(com_struct->args, ' ')
		&& ft_strchr(com_struct->args, ' ') - com_struct->args > 0)
		com_struct->com = ft_substr(com_struct->args, 0,
				ft_strchr(com_struct->args, ' ') - com_struct->args);
	if (com_struct->com == NULL)
		com_struct->com = ft_strtrim(com_struct->args, " \t\r\f\v\n");
}

void	init_command(char *command, t_command *com_struct)
{
	com_struct->out_file_app_num = char_numb(command, '>', 1, 1);
	com_struct->out_file_num = char_numb(command, '>', 0, 1);
	com_struct->in_file_num = char_numb(command, '<', 0, 1);
	com_struct->expected_words_num = char_numb(command, '<', 1, 1);
}

void	init_inputfile_param(t_command *com_struct)
{
	if (com_struct->in_file_num == 0)
		com_struct->inputfiles = NULL;
	else
	{
		com_struct->inputfiles = malloc(sizeof(char *)
				* (com_struct->in_file_num + 1));
		tab_init(com_struct->inputfiles, com_struct->in_file_num + 1);
	}
}

void	init_outputfile_param(t_command *com_struct)
{
	if (com_struct->out_file_num == 0)
		com_struct->outputfiles = NULL;
	else
	{
		com_struct->outputfiles = malloc(sizeof(char *)
				* (com_struct->out_file_num + 1));
		tab_init(com_struct->outputfiles, com_struct->out_file_num + 1);
	}
}

void	cmd_init(char *command, t_command *com_struct)
{
	init_command(command, com_struct);
	init_inputfile_param(com_struct);
	init_outputfile_param(com_struct);
	if (com_struct->expected_words_num == 0)
		com_struct->read_from_shell = NULL;
	else
	{
		com_struct->read_from_shell = malloc(sizeof(char *)
				* (com_struct->expected_words_num + 1));
		tab_init(com_struct->read_from_shell,
			com_struct->expected_words_num + 1);
	}
	if (com_struct->out_file_app_num == 0)
		com_struct->output_files_append = NULL;
	else
	{
		com_struct->output_files_append = malloc(sizeof(char *)
				* (com_struct->out_file_app_num + 1));
		tab_init(com_struct->output_files_append,
			com_struct->out_file_app_num + 1);
	}
	com_struct->com = NULL;
	com_struct->args = NULL;
}
