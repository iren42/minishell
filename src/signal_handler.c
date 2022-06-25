/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:21:24 by iren              #+#    #+#             */
/*   Updated: 2022/06/25 05:20:59 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_prompt(int signum)
{
	if (signum == SIGINT)
	{
		g_errno = 130;
		ft_putendl_fd("", STDOUT);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_errno = 130;
	}
}

void	sig_prompt_child(int signum)
{
	if (signum == SIGINT)
	{
		g_errno = 130;
		ft_putendl_fd("", STDOUT);
	}
}

void	signal_handler(void)
{
	sigset_t	signals;

	sigemptyset(&signals);
	sigaddset(&signals, SIGQUIT);
	sigaddset(&signals, SIGINT);
	signal(SIGINT, sig_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_handler_child(void)
{
	sigset_t	signals;

	sigemptyset(&signals);
	sigaddset(&signals, SIGQUIT);
	sigaddset(&signals, SIGINT);
	signal(SIGINT, sig_prompt_child);
	signal(SIGQUIT, SIG_IGN);
}
