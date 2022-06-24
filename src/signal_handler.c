/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:21:24 by iren              #+#    #+#             */
/*   Updated: 2022/06/25 01:08:17 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_prompt(int signum)
{
	if (signum == SIGINT)
	{
		g_errno = 130;
		ft_putendl_fd("", STDIN);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handler(void)
{
	signal(SIGINT, sig_prompt);
	signal(SIGQUIT, SIG_IGN);
}
