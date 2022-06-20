/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:27:25 by iren              #+#    #+#             */
/*   Updated: 2022/06/20 12:48:41 by iren             ###   ########.fr       */
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
	char	*prompt;

	(void)ac;
	(void)av;
	(void)env;
	if (ac > 1)
		ft_error(TOO_MANY_ARG, 1);
	signal_handler();
	prompt = ft_strdup(PUR"> "RESET);
	while (1)
	{
		printf("%s", prompt);
		s = readline(0);
		if (s == NULL)
		{
			// free all
			printf("\n");
			exit(0);
		}
		add_history(s);
		init_tmini(s, env, &mini);
		mini.s = expander(s);
		mini.token_list = lexer(&mini);
		mini.cmdtab_list = parser(&mini);
		print_tmini(&mini);
		ft_lstclear(&mini.token_list, del_token);
		ft_lstclear(&mini.cmdtab_list, del_cmdtab);
		free(mini.s);
		free(s);	
	}
	free(prompt);
	rl_clear_history();
}
