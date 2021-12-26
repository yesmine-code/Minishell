/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 20:04:27 by mrahmani          #+#    #+#             */
/*   Updated: 2021/12/26 17:35:43 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_with_arg(char *s)
{
	int		i;

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

int	ft_env(t_env *env, char **arg)
{
	if (env == NULL)
		return (1);
	if (env_with_arg(arg[1]) == 0 && arg[1] != NULL)
	{
		printf("env: '%s': No such file or directory\n", arg[1]);
		return (127);
	}
	else
	{
		while (env)
		{
			printf("%s\n", env->var);
			env = env->next;
		}
	}
	return (0);
}

void	add_env(t_env **env, char *str)
{
	t_env	*tmp;
	t_env	*new;

	tmp = *env;
	new = malloc(sizeof(t_env));
	if (new == NULL)
		return ;
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

void	init_env(t_shellinfo *shell, char **env)
{
	t_env	*tmp;

	tmp = NULL;
	while (*env)
	{
		add_env(&tmp, *env);
		env++;
	}
	shell->env = tmp;
}
