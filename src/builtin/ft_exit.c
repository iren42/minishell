/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:07:54 by iren              #+#    #+#             */
/*   Updated: 2022/06/21 15:36:53 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_cmdtab *c)
{
	t_mini *m;

	if (c)
	{
		// exit should not work if arg_list != 0
		if (c->arg_list != 0)
		{
			print_error("shell: exit", NULL, 0, "too many arguments");
			return (FAILURE);
		}
	m = c->m;
/*		ft_lstclear(&m->token_list, del_token);
		ft_lstclear(&m->cmdtab_list, del_cmdtab);

		free(m->s);
		ft_lstclear(&m->env_list, del_env);
		rl_clear_history();
	*/	exit(0);

	}
	return (SUCCESS);
}
