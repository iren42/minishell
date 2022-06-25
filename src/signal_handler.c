/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:21:24 by iren              #+#    #+#             */
/*   Updated: 2022/06/25 05:06:47 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_prompt(int signum)
{
	if (signum == SIGINT)
	{
		ft_putendl_fd("", STDOUT);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_errno = 130;
	}
}

void	signal_handler(void)
{
	signal(SIGINT, sig_prompt);
	signal(SIGQUIT, SIG_IGN);
}
