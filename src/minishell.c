/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:27:25 by iren              #+#    #+#             */
/*   Updated: 2022/06/20 23:19:07 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_tmini(char *s, char **env, t_mini *mini)
{
	mini->s = s;
	mini->env = env;
	mini->token_list = 0;
	mini->cmdtab_list = 0;
	mini->env_list = 0;
	mini->fd = 0;
}
void	init_env(t_mini *m, char **env)
{
	t_env	*new;
	char	*value;
	int	i;

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
			ft_lstadd_back(&m->env_list, ft_lstnew(new));
			i++;
		}
	}

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
		init_env(&mini, env);
	//print_list(mini.env_list, &print_env);

		print_tmini(&mini);

executor(&mini);
		
		ft_lstclear(&mini.env_list, del_env);
		ft_lstclear(&mini.token_list, del_token);
		ft_lstclear(&mini.cmdtab_list, del_cmdtab);
	//	ft_pwd(mini.cmdtab_list);
	//	ft_env(&mini);
		free(mini.s);
		free(s);	
	}
	free(prompt);
	rl_clear_history();
}
