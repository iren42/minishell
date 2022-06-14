/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:27:25 by iren              #+#    #+#             */
/*   Updated: 2022/06/09 22:55:25 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_tmini(char *s, char **env, t_mini *mini)
{
	mini->s = s;
	mini->s_split = 0;
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
	if (ac > 1)
		ft_error(TOO_MANY_ARG, 1);
	s = readline(PROMPT);
	while (s != NULL)
	{
		init_tmini(s, env, &mini);
		lexer(&mini);
		print_tmini(&mini);
		s = readline(PROMPT);
	}
}
