/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 13:20:37 by ybesbes           #+#    #+#             */
/*   Updated: 2021/10/26 21:35:00 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **get_paths()
{
	char *path;
	char **path_tab;
	int i;

	i = 0;
	path = getenv("PATH");
	path_tab = ft_split(path, ':');
	return (path_tab);
}

char *find_cmd_path(char *cmd)
{
	char **path_tab;
	int i;
	char *tmp;
	char *tmp2;

	i = 0;
	path_tab = get_paths();
	while (path_tab[i] != NULL)
	{
		tmp2 = ft_strjoin(path_tab[i], "/");
		tmp = ft_strjoin(tmp2, cmd);
		free(tmp2);
		if (access(tmp, F_OK) == 0)
			return(tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

int quotes_enum(char *str)
{
	int i;
	int quotes_num;
	int double_quotes_num;

	i = 0;
	double_quotes_num = 0;
	quotes_num = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\'))
		{
			double_quotes_num++;
			i++;
			while (str[i] != '\0' && (str[i] != '\"' || str[i - 1] == '\\'))
				i++;
			double_quotes_num++;
		}
		if (str[i] == '\'')
		{
			quotes_num++;
			i++;
			while (str[i] != '\0' && str[i] != '\'')
				i++;
			quotes_num++;
		}
		i++;
	}
	return (quotes_num + double_quotes_num);
}

void	ft_remove_char(char *str,int pos)
{
	int i;

	i = 0;
	while (str[pos] != '\0')
	{
		str[pos] = str[pos + 1];
		pos++;
	}
}

void	remove_quotes(char *str, int *pos_tab)
{
	int i;

	i = quotes_enum(str) - 1;
	while (i >= 0)
	{
		ft_remove_char(str, pos_tab[i]);
		i--;
	}
}

void	ft_delete_quotes(char *com)
{
	int i;
	int *pos_tab;
	int j;


	i = 0;
	j = 0;
	pos_tab = malloc(sizeof(int) * (quotes_enum(com) + 1));
	while (com[i] != '\0')
	{
		if (com[i] == '\"' && (i == 0 || com[i - 1] != '\\'))
		{
			pos_tab[j] = i;
			j++;
			i++;
			while (com[i] != '\0' && (com[i] != '\"' || com[i - 1] == '\\'))
				i++;
			pos_tab[j] = i;
			j++;
		}
		if (com[i] == '\'')
		{
			pos_tab[j] = i;
			j++;
			i++;
			while (com[i] != '\0' && com[i] != '\'')
				i++;
			
			pos_tab[j] = i;
			j++;
		}
		i++;
	}
	pos_tab[j] = '\0';
	remove_quotes(com, pos_tab);
}
int		is_it_between_simple_quotes(char *str, int pos)
{

	int i;
	int result;

	i = 0;
	result = 0;
	while (i < pos)
	{
		if (str[i] == '\'')
			result++;
		i++;
	}
	if (result % 2 != 0)
		return (1);
	return (0);
	

}
int		is_it_between_quotes(char *str, int pos)
{
	int i;
	int result;
	int result1;

	i = 0;
	result = 0;
	while (i < pos)
	{
		if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\'))
		{
			result1++;
			while ((str[i] != '\"' || str[i - 1] == '\\') && str[i] != '\0')
				i++;
		}
		if (str[i] == '\'')
			result++;
		i++;
	}
	if (result % 2 != 0 || result1 % 2 != 0)
		return (1);
	return (0);
}


char *substitute_env_var(char *com)
{
	int i;
	int tmp;
	char *env;
	char **str;
	int char_to_extract;
	int char_to_add;
	int j;

	i = 0;
	j = 0;
	char_to_extract = 0;
	char_to_add =0;

	str = malloc(sizeof(char *) * char_numb(com, '$', 0));
	while (com[i] != '\0')
	{
		if (com[i] == '$')
		{
			//printf("hi");
			i++;
			tmp = i;
			while (ft_isalnum(com[i]) == 1)
				i++;
			env = ft_substr(com, tmp, i - tmp);
			char_to_extract = char_to_extract + ft_strlen(env) + 1;
			str[j] = getenv(env);
			//printf("%s", str[j]);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < char_numb(com, '$', 0))
	{
		if (str[i] != NULL)
			char_to_add = char_to_add + ft_strlen(str[i]);
		i++;
	}
	env = malloc(sizeof(char) * (ft_strlen(com) - char_to_extract + char_to_add));
	i = 0;
	j = 0;
	int k = 0;
	tmp = 0;
	while (com[i] != '\0')
	{
		if (com[i] == '$' && is_it_between_simple_quotes(com, i) == 0 && ft_isspace(com[i + 1]) != 1 && com[i + 1] != '\0')
		{
			i++;
			while (ft_isalnum(com[i]) == 1)
				i++;
			if (str != NULL && str[tmp] != NULL)
			{
				k = 0;
				while (str[tmp][k] != '\0')
				{
					env[j] =  str[tmp][k];
					j++;
					k++;
				}
				tmp++;
			}
		}
		else
		{
			env[j] = com[i];
			i++;
			j++;
		}
	}
	env[j] = '\0';
	return (env);
}