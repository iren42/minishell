/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:31:53 by iren              #+#    #+#             */
/*   Updated: 2022/06/21 04:52:25 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmdtab	*c)
{
	char	*pwd;
	t_list	*l;
	
	l = c->m->env_list;
	if (l != 0)
	{
		while (l)
		{
			if (ft_memcmp(get_env_name(l->content), "PWD", 4) == 0)
			{
				printf("%s\n", get_env_value(l->content));
				return (SUCCESS) ;
			}
			l = l->next;
		}
	}
	return (FAILURE);
}
