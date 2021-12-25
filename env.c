/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 20:04:27 by mrahmani          #+#    #+#             */
/*   Updated: 2021/12/25 13:07:42 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int env_with_arg(char *s)
{
	int i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int ft_env(t_env *env, char **arg)
{
	if (env == NULL)
		return (1);
	if (env_with_arg(arg[1]) == 0)
	{
		printf("env: '%s': No such file or directory\n", arg[1]);
		return (127);
	}
	while (env)
	{
		printf("%s\n", env->var);
		env = env->next;
	}
	return (0);
}

void add_env(t_env **env, char *str)
{
	t_env *tmp;
	t_env *new;

	tmp = *env;
	if (!(new = malloc(sizeof(t_env))))
		return;
	if (*env == NULL)
	{
		*env = new;
		(*env)->next = NULL;
		(*env)->var = ft_strdup(str);
		(*env)->value = get_value(str);
		(*env)->name = get_name_env(str);
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		tmp->next->var = ft_strdup(str);
		tmp->next->value = get_value(str);
		tmp->next->name = get_name_env(str);
		tmp->next->next = NULL;
	}
}

void init_env(t_shellinfo *shell, char **env)
{
	t_env *tmp;

	tmp = NULL;
	while (*env)
	{
		add_env(&tmp, *env);
		env++;
	}
	shell->env = tmp;
}

char *get_value(char *s)
{
	int i;
	int count;
	char *tmp;

	i = 0;
	count = 0;
	if (s != NULL)
	{
		while (s[i])
		{
			count++;
			if (s[i] == '=')
			{
				tmp = ft_substr(s, i + 1, ft_strlen(s) - count);
				return (tmp);
			}
			i++;
		}
	}
	return (ft_strdup(s));
}

char *get_name_env(char *s)
{
	int i;

	i = 0;
	if (s == NULL)
		return (ft_strdup(""));
	while (s[i])
	{
		if (s[i] == '=')
			return (ft_substr(s, 0, i));
		i++;
	}
	return (ft_strdup(s));
}
