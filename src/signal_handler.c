/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:21:24 by iren              #+#    #+#             */
/*   Updated: 2022/06/20 12:47:37 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_prompt(int signum)
{
	char	*prompt;
	if (signum == SIGINT)
	{
		printf("\n");
	 rl_on_new_line();
	 rl_replace_line("", 1);
		prompt = ft_strdup(GRN "> "RESET);
			printf("%s", prompt);
		free(prompt);
	//	signal(SIGINT, &sig_prompt); A quoi ca sert ?
	}
}

void	sig_quit(int signum)
{
	printf("quit\n");
	exit(0);
}

void	signal_handler()
{
		signal(SIGINT, sig_prompt);
		signal(SIGQUIT, SIG_IGN);
}

