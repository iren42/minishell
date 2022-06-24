/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:27:25 by iren              #+#    #+#             */
/*   Updated: 2022/06/24 16:32:29 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_errno = 0;

void	update_tmini(char *s, t_mini *mini)
{
	mini->token_list = 0;
	mini->cmdtab_list = 0;

	mini->s = s;
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

void	init_tmini(char **env, t_mini *mini)
{
	t_list	*env_list;
	char	builtins[] =  "export cd pwd echo unset env exit";

	env_list = init_env_list(env);
	mini->env_list = env_list;
	mini->split_builtin = ft_split(builtins, ' ');
	//	print_split(mini->split_builtin);
	if (!mini->split_builtin)
		exit(1);
	mini->token_list = 0;
	mini->cmdtab_list = 0;

}

int	main(int ac, char **av, char **env)
{
	char	*s;
	int	ret;
	t_mini	mini;

	(void)av;
	if (ac > 1)
		ft_error(TOO_MANY_ARG, 1);
	signal_handler();
	init_tmini(env, &mini);
	while (1)
	{
		s = ft_readline();
	//	printf("right after readline s %s\n", s);
		if (s == NULL)
		{
			// free all
			ft_lstclear(&mini.env_list, del_env);
			rl_clear_history();
			free_split(mini.split_builtin);
			ft_putendl_fd("Quit.", STDIN);
			return (0);
		}
	//	printf("after readline s %s\n", s);
		mini.s = s;
		ret = expander(&mini);
		if (ret == 0)
		{
			print_error("shell", 0, errno, "syntax error main");
			continue;
	}
//		mini.token_list = lexer(&mini);
		ret = lexer(&mini);
		mini.cmdtab_list = parser(&mini);

//		print_tmini(&mini);

		ret = executor(&mini);

		ft_lstclear(&mini.token_list, del_token);
		ft_lstclear(&mini.cmdtab_list, del_cmdtab);

		free(mini.s);
	//	free(s);	
	}
	ft_lstclear(&mini.env_list, del_env);
	rl_clear_history();
}
