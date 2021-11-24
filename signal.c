/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 21:03:47 by mrahmani          #+#    #+#             */
/*   Updated: 2021/11/24 23:18:19 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ctrl_c_handler(int sig, siginfo_t *info, void *context)
{
    printf("\n");
    if (info->si_pid != 0)
    {
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void handle_ctrl_c()
{
    struct sigaction sa;

    sa.sa_sigaction = ctrl_c_handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &sa, NULL);
}

void ctrl_backslash_handler(int sig, siginfo_t *info, void *context)
{
    if (info->si_pid == 0)
    {
        printf("Quit\n");
    }
    else
        printf("\b\b  \b\b");
}

void handle_ctrl_backslash()
{
    struct sigaction sa;

    sa.sa_sigaction = ctrl_backslash_handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGQUIT, &sa, NULL);
}