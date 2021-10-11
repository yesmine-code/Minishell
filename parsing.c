/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 10:46:19 by ybesbes           #+#    #+#             */
/*   Updated: 2021/10/04 10:46:24 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int word_alpha(char *str)
{
	int i;
	i = 0;

	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void cmd_init(char *command, t_command *com_struct)
{
	com_struct->out_file_app_num = char_numb(command, '>', 1);
	com_struct->out_file_num = char_numb(command, '>', 0);
	com_struct->in_file_num = char_numb(command, '<', 0);
	com_struct->expected_words_num = char_numb(command, '<', 1);
	com_struct->inputfiles = malloc(sizeof(char *) * (com_struct->in_file_num + 1));
	com_struct->outputfiles = malloc(sizeof(char *) * (com_struct->out_file_num + 1));
	com_struct->read_from_shell = malloc(sizeof(char *) * (com_struct->expected_words_num + 1));
	com_struct->output_files_append = malloc(sizeof(char *) * (com_struct->out_file_app_num + 1));
}

t_command get_cmd(char *command)
{
	t_command com_struct;
	char *com_trim;
	int i;
	
	i = 0;
	cmd_init(command, &com_struct);
	com_trim = ft_strtrim(command, " \t\r\f\v\n")
	while (com_trim[i] != '\0')
	{
		if (com_trim[i])


	}
}
int	char_numb(char *str, char c, int two)
{
	int	i;
	int	r;
	int rd;

	r = 0;
	rd = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			if (str[i + 1] != c)
				r++;
			else
			{
				rd++;
				i++;
			}
		}
		i++;
	}
	if (two == 0)
		return (r);
	return (rd);
}

char **read_from_input(char *str)
{
	int	input_double_num;
	char **input_double;
	char *tmp;
	int	i;
	int j;
	int	k;

	i = 0;
	k = 0;
	input_double_num = char_numb(str, '<', 1);
	input_double = malloc(sizeof(char **) * input_double_num + 1);
	if (input_double == NULL)
		return (NULL);
	tmp = NULL;
	input_double[input_double_num] = 0;
	while(str[i] != '\0' && k < input_double_num )
	{
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] != '\0')
		{
			tmp = malloc(sizeof(char *) * ft_strlen(str - 2));
			if (tmp == NULL)
			{
				free(input_double);
				return NULL;
			}
			j = 0;
			i = i + 2;
			while (str[i] == ' ')
				i++;
			while (str[i] != ' ' && str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i] != '\0')
				tmp[j++] = str[i++];
			tmp[j] = '\0';
			input_double[k++] = tmp;
		}
		else
			i++;
	}
	return 	(input_double);
}