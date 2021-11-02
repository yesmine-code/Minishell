/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 10:48:04 by ybesbes           #+#    #+#             */
/*   Updated: 2021/10/31 17:09:54 by mrahmani         ###   ########.fr       */
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


typedef struct  s_env
{
	char *var;
	struct s_env *next;
} t_env;
typedef struct s_command
{
	t_env *env;
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
int pipe_cmd(t_command com, int is_previous, int is_coming, int *old_pipe[], int last_child_status, char **env);
int ft_pwd(void);
int ft_exit(void);
int is_builtin(char *str);
t_command get_cmd(char *command, char **env);
void parse_cmd(char *command, t_command *com_struct);
void ft_free_cmd(t_command *com);
char **get_paths();
char *find_cmd_path(char *cmd);
void ft_skip_quotes(char *str, int *i);
char			**ft_mini_split(char *s, char c);
void		*mini_leak(char **ptr, int words);
void ft_free_tab(char **str);
int quotes_enum(char *str);
int		is_it_between_quotes(char *str, int pos);
void	ft_delete_quotes(char *com);
char *substitute_env_var(char *com);
int		is_it_between_simple_quotes(char *str, int pos);
int		ft_mini_count(char *s, char c);
//t_command get_cmd(char *command);
int handle_single_cmd(char* cmd, char **env);
int execute_cmd(t_command com);
int ft_cd(char **dir);
int ft_echo(char **arg);
//int ft_env(char **env);
int ft_env(t_env *env);
int init_env(t_command *com, char **env_);

#endif