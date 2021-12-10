/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:59:29 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/02 22:16:42 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
int ft_exit(t_env *env_list)
{
	free_env_list(env_list);
	exit(EXIT_SUCCESS);
=======
void ft_exit(t_shellinfo shell, int stat)
{
	free_env_list(shell.env);
	if (stat == 0)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
>>>>>>> 989334766fec09f58424eb6def1f1a3b402efdeb
}
