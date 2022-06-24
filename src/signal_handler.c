/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:21:24 by iren              #+#    #+#             */
/*   Updated: 2022/06/24 11:47:06 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_prompt(int signum)
{
	if (signum == SIGINT)
	{
g_errno = 130;
		ft_putendl_fd("", STDIN);
		//printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	//	ft_putendl_fd("after ctrl c", STDIN);	
		//	signal(SIGINT, &sig_prompt); A quoi ca sert ?
	}
}

void	signal_handler()
{
	signal(SIGINT, sig_prompt);
	signal(SIGQUIT, SIG_IGN);
}

