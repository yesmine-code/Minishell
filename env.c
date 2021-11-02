/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 20:04:27 by mrahmani          #+#    #+#             */
/*   Updated: 2021/10/31 17:09:42 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int ft_env(char **env)
// {
//     int index = 0;

//     if (env == NULL)
//         return (-1);
//     while (env[index])
//     {
//         printf("%s\n", env[index++]);
//     }
//     printf("nb parms env: %d\n", index);
//     return (0);
// }

int ft_env(t_env *env)
{
    int count = 0;
    while (env && env->next != NULL)
    {
        printf("%s\n", env->var);
        env = env->next;
        count++;
    }
    if (env)
        printf("%s\n", env->var);
    //printf("lines env: %i\n", count);
    return (0);
}

int init_env(t_command *com, char **env_)
{
	int		i;
    t_env *tmp_env;
    t_env *new_env;

	if (!(tmp_env = malloc(sizeof(t_env))))
		return -1;
    tmp_env->var = ft_strdup(env_[0]);
    tmp_env->next = NULL;
    com->env = tmp_env;
    i = 1;
	while (env_  && env_[0] && env_[i])
	{
        if (!(new_env =  malloc(sizeof(t_env))))
            return -1;
		new_env->var = ft_strdup(env_[i]);
        //printf("%s\n", new_env->var);
		new_env->next = NULL;
		tmp_env->next = new_env;
        tmp_env = new_env;
		i++;
	}
    //printf("lines env_init:%d \n", i);
    return 0;
}