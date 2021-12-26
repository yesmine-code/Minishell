/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 10:21:10 by mrahmani          #+#    #+#             */
/*   Updated: 2021/12/26 21:24:01 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exists(char *s, t_env *env, t_env **new_env)
{
	t_env	*tmp;
	char	*name_of_new_env;

	tmp = env;
	name_of_new_env = get_name_env(s);
	while (tmp != NULL)
	{
		if (ft_strcompare(tmp->name, name_of_new_env) == 1)
		{
			free(name_of_new_env);
			*new_env = tmp;
			return (1);
		}
	tmp = tmp->next;
	}
	free(name_of_new_env);
	return (0);
}

int	is_valid_env(char *s)
{
	int		i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (s[i] == '_')
			i++;
		else if (ft_isalnum(s[i]) == 0 || (i == 0 && ft_isdigit(s[i]) == 1))
			return (0);
	i++;
	}
	return (1);
}

int	is_valid_ident(char *s, int *ret)
{
	char	*env_name;

	if (s == NULL)
		return (1);
	env_name = get_name_env(s);
	if (is_valid_env(env_name) == 0)
	{
		printf("export: '%s': not a valid identifier\n", s);
		*ret = 1;
		free(env_name);
		return (0);
	}
	free(env_name);
	return (1);
}

void	update_env(t_env *env_to_update, char *arg)
{
	if (env_to_update->var != NULL)
		free(env_to_update->var);
	env_to_update->var = ft_strdup(arg);
	if (env_to_update->value != NULL)
		free(env_to_update->value);
	env_to_update->value = get_value(arg);
	if (env_to_update->name != NULL)
		free(env_to_update->name);
	env_to_update->name = get_name_env(arg);
}

int	ft_export(t_env *env, char **arg)
{
	t_env	*new_env;
	t_env	*env_to_update;
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	if (arg[1] == NULL)
		return (without_arg(env));
	while (arg[i] != NULL)
	{
		if (is_valid_ident(arg[i], &ret) == 0)
			i++;
		else if (arg[i] != NULL && is_new_env(arg[i]) == 1)
		{
			if (exists(arg[i], env, &new_env) == 0)
				add_env(&env, arg[i]);
			else if (exists(arg[i], env, &env_to_update) == 1)
				update_env(env_to_update, arg[i]);
			i++;
		}
		else
			i++;
	}
	return (ret);
}
