/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 10:46:19 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/20 23:31:55 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word(char *command, int *i)
{
	int	tmp;

	while (ft_isspace(command[*i]) == 1)
		*i = *i + 1;
	tmp = *i;
	while (ft_isspace(command[*i]) == 0 && command[*i] != '\0')
		*i = *i + 1;
	return (ft_substr(command, tmp, *i - tmp));
}

void	parse_single_input_redirect(char *command, int *position
		, t_command *com_struct)
{
	if (command[*position] == '<' && command[(*position) + 1] != '<'
		&& is_it_between_quotes(command, *position) == 0)
	{
		*position += 1;
		com_struct->inputfiles[tab_next_index(com_struct->inputfiles)]
			= get_word(command, position);
	}
}

void	parse_double_input_redirect(char *command
		, int *position, t_command *com_struct)
{
	if (command[*position] == '<' && command[(*position) + 1] == '<'
		&& is_it_between_quotes(command, *position) == 0)
	{
		*position += 2;
		com_struct->read_from_shell[tab_next_index(com_struct->read_from_shell)]
			= get_word(command, position);
	}
}

void	parse_single_output_redirect(char *command, int *position
		, t_command *com_struct)
{
	if (command[*position] == '>' && command[(*position) + 1] != '>'
		&& is_it_between_quotes(command, *position) == 0)
	{
		*position += 1;
		com_struct->outputfiles[tab_next_index(com_struct->outputfiles)]
			= get_word(command, position);
	}
}

void	parse_double_output_redirect(char *command, int *position
		, t_command *com_struct)
{
	if (command[*position] == '>' && command[(*position) + 1] == '>'
		&& is_it_between_quotes(command, *position) == 0)
	{
		*position += 2;
		com_struct->output_files_append[tab_next_index
			(com_struct->output_files_append)] = get_word(command, position);
	}
}
