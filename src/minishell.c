/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:27:25 by iren              #+#    #+#             */
/*   Updated: 2022/06/21 02:30:22 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_tmini(char *s,t_list *env_list, t_mini *mini)
{
	mini->s = s;
//	mini->env = env;
	mini->token_list = 0;
	mini->cmdtab_list = 0;
	mini->env_list = env_list;
	mini->fd = 0;
}
t_list	*init_env(char **env)
{
	t_env	*new;
	char	*value;
	t_list	*env_list;
	int	i;

	env_list = 0;
	if (env)
	{
		i = 0;
		while (env[i])
		{
			new = malloc(sizeof(t_env));
			if (!new)
				exit(1);
			new->name = ft_strdup(env[i]);
			new->value = 0;
			value = getenv(env[i]);
			if (value)
				new->value = ft_strdup(value);
			ft_lstadd_back(&env_list, ft_lstnew(new));
			i++;
		}
	}
	return (env_list);
}

void	del_env(void *o)
{
	t_env	*e;

	e = (t_env *)o;
	free(e->name);
	free(e->value);
	free(e);
}

int	main(int ac, char **av, char **env)
{
	char	*s;
	t_mini	mini;
	char	*prompt;
	t_list	*env_list;

	(void)ac;
	(void)av;
	(void)env;
	env_list = 0;
	if (ac > 1)
		ft_error(TOO_MANY_ARG, 1);
	signal_handler();
	env_list = init_env(env);
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
		init_tmini(s, env_list, &mini);
		mini.s = expander(&mini);
		mini.token_list = lexer(&mini);
		mini.cmdtab_list = parser(&mini);
//	print_list(mini.env_list, &print_env);

		print_tmini(&mini);
		
		ft_lstclear(&mini.token_list, del_token);
		ft_lstclear(&mini.cmdtab_list, del_cmdtab);
	//	ft_pwd(mini.cmdtab_list);
	//	ft_env(&mini);
		ft_export(&mini);
		free(mini.s);
		free(s);	
	}
	free(prompt);
		ft_lstclear(&mini.env_list, del_env);
	rl_clear_history();
}
