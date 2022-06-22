/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:27:25 by iren              #+#    #+#             */
/*   Updated: 2022/06/22 16:43:25 by gufestin         ###   ########.fr       */
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

t_list	*init_env_list(char **env)
{
	t_env	*new;
	char	*value;
	t_list	*env_list;
	int	len;
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
			len = get_len_env_name(env[i]);
			new->name = ft_substr(env[i], 0,len);
			new->value = ft_substr(env[i], len + 1, ft_strlen(env[i]));
			//	print_env(new);
			ft_lstadd_back(&env_list, ft_lstnew(new));
			i++;
		}
	}
	return (env_list);
}

int	input_empty(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*ft_readline(void)
{
	char	*input;
	char	*trimed;

	input = readline(PROMPT);
	if (!input)
		return (NULL);
	if (!input_empty(input))
	{
		add_history(input);
	//	ft_putstr_fd("added in history\n", STDIN);
	}
	trimed = ft_strtrim(input, " ");
	free(input);
//	ft_putendl_fd(trimed, STDIN);
	return (trimed);
//	return (input);
}

int	main(int ac, char **av, char **env)
{
	char	*s;
	t_mini	mini;
	t_list	*env_list;
	t_cmdtab *c;

	(void)ac;
	(void)av;
	(void)env;
	env_list = 0;
	if (ac > 1)
		ft_error(TOO_MANY_ARG, 1);
	signal_handler();
	env_list = init_env_list(env);
	while (1)
	{
		s = ft_readline();
		if (s == NULL)
		{
			// free all
			ft_putendl_fd("", STDIN);
			exit(0);
		}

		init_tmini(s, env_list, &mini);
		mini.s = expander(&mini);
		mini.token_list = lexer(&mini);
		mini.cmdtab_list = parser(&mini);

		print_tmini(&mini);

	//	executor(&mini);
		
		//	ft_unset(mini.cmdtab_list->content);
		//		ft_pwd(mini.cmdtab_list->content);
		//		ft_export(mini.cmdtab_list->content);
		//	ft_env(mini.cmdtab_list->content);
				ft_exit(mini.cmdtab_list->content);
		//	ft_cd(mini.cmdtab_list->content);
//		ft_echo(mini.cmdtab_list->content);
		ft_lstclear(&mini.token_list, del_token);
		ft_lstclear(&mini.cmdtab_list, del_cmdtab);

		free(mini.s);
		free(s);	
	}
	ft_lstclear(&mini.env_list, del_env);
	rl_clear_history();
}
