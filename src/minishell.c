/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:27:25 by iren              #+#    #+#             */
/*   Updated: 2022/06/18 14:27:14 by isabelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_tmini(char *s, char **env, t_mini *mini)
{
	mini->s = s;
	mini->env = env;
	mini->token_list = 0;
	mini->cmdtab_list = 0;
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
	//	printf("s=%s", s);
		init_tmini(s, env, &mini);
		mini.s = expander(s);
		mini.token_list = lexer(&mini);
		mini.cmdtab_list = parser(&mini);
		ft_lstclear(&mini.token_list, del_token);
		ft_lstclear(&mini.cmdtab_list, del_cmdtab);
	//	print_tmini(&mini);
		
		s = readline(PROMPT);
		
	}
}
