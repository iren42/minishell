/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:27:25 by iren              #+#    #+#             */
/*   Updated: 2022/06/25 05:21:13 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_tmini(char *s, t_mini *mini)
{
	mini->token_list = 0;
	mini->cmdtab_list = 0;
	mini->s = s;
	mini->fd = 0;
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

	if (g_errno != 130)
		input = readline(PROMPT);
	else
		input = readline("");
	if (!input)
		return (NULL);
	if (!input_empty(input))
		add_history(input);
	trimed = ft_strtrim(input, " ");
	free(input);
	return (trimed);
}

int	clear_exit(t_mini mini)
{
	ft_lstclear(&mini.env_list, del_env);
	rl_clear_history();
	free_split(mini.split_builtin);
	ft_putendl_fd("exit", STDIN);
	return (0);
}

void	call_and_clear(t_mini *mini)
{
	lexer(mini);
	mini->cmdtab_list = parser(mini);
	executor(mini);
	ft_lstclear(&mini->token_list, del_token);
	ft_lstclear(&mini->cmdtab_list, del_cmdtab);
	free(mini->s);
}
