/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:24:27 by iren              #+#    #+#             */
/*   Updated: 2022/06/24 22:25:13 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_cmdtab *c)
{
	t_list	*l;

	if (c->m->env_list)
	{
		l = c->m->env_list;
		if (c->arg_list != 0)
			return (FAILURE);
		while (l)
		{
			printf("%s=%s\n", get_env_name(l->content),
				get_env_value(l->content));
			l = l->next;
		}
		return (SUCCESS);
	}
	return (FAILURE);
}
