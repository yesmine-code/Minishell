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

/*char *PATH;

int main(void)
{
	char	*str;
	char *str1;
	char* argv[] = { NULL };
	char* envp[] = { NULL };
	pid_t child_pid;
	int child_status;
	pid_t tpid;
	int	pfd[2];

	str1 = NULL;
	PATH = "commands/";
	char **read_from_shell;
	char **commands;
	char **outputfiles;
	char **inputfiles;
	char **outputfiles_append;
	int	i;
	i = 0;
	while (1)
	{
	
		str = readline("minishell->");
		add_history(str);
		if (check_syntax_errors(str) == 1)
		{
			perror("please enter a valid command");
			free(str);
		}
		read_from_shell = read_from_input(str);
		commands = malloc(sizeof(char *) * (char_numb(str, '|', 0) + 1));
		if (commands == NULL)
		{
			perror("malloc failed");
			free(str);
			return (0);
		}
		outputfiles = malloc(sizeof(char *) * char_numb(str, '>', 0));
		outputfiles_append = malloc(sizeof(char *) * char_numb(str, '>', 1));
		inputfiles = malloc(sizeof(char *) * char_numb(str, '<', 0));
		while(read_from_shell[i] != 0)
		{
			printf("%s\n", read_from_shell[i]);
			i++;
		}
		i = 0;
		commands = ft_split(str, '|');
		while(commands[i] != 0)
		{
			printf("%s\n", commands[i]);
			i++;
		}
		if (ft_strncmp(str, "exit", ft_strlen(str)) == 0)
		{
			free(str);
			exit (EXIT_SUCCESS);			
		}
		child_pid = fork();
		if (child_pid < 0)
		{
			free(str);
			perror("creating fork failed\n")
		}
		if (child_pid == 0)
		{
			str1 = ft_strjoin(PATH, str);
			close(pfd[1]);
			dup2(pfd[0], 0);
			dup2(pfd[0], 0);
			execve(str1,argv, envp);
			perror("please enter a valid command\n");
			exit (EXIT_SUCCESS);*/			
	

int main()
{
	char *str;
	char *tmp;
	char **commands;


	while (1)
	{
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
			pipe_cmd(commands);
		}
	}

}

