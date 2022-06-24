/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:23:02 by iren              #+#    #+#             */
/*   Updated: 2022/06/25 01:03:30 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *name, t_list *env_list)
{
	t_list	*l;

	l = env_list;
	if (env_list != 0 && name)
	{
		while (l)
		{
			if (ft_memcmp(get_env_name(l->content), name,
					ft_strlen(name) + 1) == 0)
				return (get_env_value(l->content));
			l = l->next;
		}
	}
	return (0);
}

t_env	*ft_getenv_ptr(char *name, t_list *env_list)
{
	t_list	*l;

	l = env_list;
	if (env_list != 0 && name)
	{
		while (l)
		{
			if (ft_memcmp(get_env_name(l->content), name,
					ft_strlen(name) + 1) == 0)
				return (l->content);
			l = l->next;
		}
	}
	return (0);
}

void	del_env(void *o)
{
	t_env	*e;

	e = (t_env *)o;
	free(e->name);
	free(e->value);
	free(e);
}

char	*get_env_name(void *o)
{
	t_env	*e;

	e = (t_env *)o;
	if (e)
		return (e->name);
	else
		return (0);
}

char	*get_env_value(void *o)
{
	t_env	*e;

	e = (t_env *)o;
	return (e->value);
}
