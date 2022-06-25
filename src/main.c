/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:36:18 by gufestin          #+#    #+#             */
/*   Updated: 2022/06/25 01:58:17 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_errno = 0;

t_list	*init_env_list(char **env)
{
	t_env	*new;
	t_list	*env_list;
	int		len;
	int		i;

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
			new->name = ft_substr(env[i], 0, len);
			new->value = ft_substr(env[i], len + 1, ft_strlen(env[i]));
			ft_lstadd_back(&env_list, ft_lstnew(new));
			i++;
		}
	}
	return (env_list);
}

void	init_tmini(char **env, t_mini *mini)
{
	t_list	*env_list;
	char	*builtins;

	env_list = init_env_list(env);
	mini->env_list = env_list;
	builtins = ft_strdup("export cd pwd echo unset env exit");
	if (!builtins)
		exit(1);
	mini->split_builtin = ft_split(builtins, ' ');
	free(builtins);
	if (!mini->split_builtin)
		exit(1);
	mini->token_list = 0;
	mini->cmdtab_list = 0;
}

int	main(int ac, char **av, char **env)
{
	char	*s;
	t_mini	mini;
	int		ret;

	(void)av;
	if (ac > 1)
		ft_error(TOO_MANY_ARG, 1);
	signal_handler();
	init_tmini(env, &mini);
	while (1)
	{
		s = ft_readline();
		if (s == NULL)
			return (clear_exit(mini));
		mini.s = s;
		ret = expander(&mini);
		if (ret == 0)
		{
			print_error("shell", 0, errno, "syntax error main");
			continue ;
		}
		call_and_clear(&mini);
	}
	ft_lstclear(&mini.env_list, del_env);
	rl_clear_history();
}
