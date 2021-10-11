/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 10:48:04 by ybesbes           #+#    #+#             */
/*   Updated: 2021/09/27 10:48:07 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <../libft/libft.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>



typedef struct s_command
{
	char	*com;
	char	*args;
	int		out_file_num;
	char 	**outputfiles;
	int		in_file_num;
	char	**inputfiles;
	int		out_file_app_num;
	char	**output_files_append;
	int		expected_words_num;
	char 	**read_from_shell;
}				t_command;

int	char_numb(char *str, char c, int two);
int	check_syntax_errors(char *str);
char **read_from_input(char *str);
int pipe_cmd(char **commands);
int ft_pwd(void);
int ft_exit(void);
int is_builtin(char *str);













#endif