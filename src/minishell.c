/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:27:25 by iren              #+#    #+#             */
/*   Updated: 2022/06/09 14:44:45 by isabelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_tmini(char *s, char **env, t_mini *mini)
{
	mini->s = s;
	mini->env = env;
	mini->tokens = 0;
	mini->fd = 0;
}

int	main(int ac, char **av, char **env)
{
	char	*s;
	t_mini	mini;

	(void)ac;
	(void)av;
	(void)env;
	s = readline(PROMPT);
	while (s != NULL)
	{
		init_tmini(s, env, &mini);
		lexer(&mini);
		print_tmini(&mini);
		s = readline(PROMPT);
	}
}
