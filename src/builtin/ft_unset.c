/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 05:12:41 by iren              #+#    #+#             */
/*   Updated: 2022/06/24 23:25:11 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*find_name_from_env(t_list *env_list, char *name)
{
	t_list	*l;
	t_list	*prev;

	if (env_list)
	{
		l = env_list;
		while (l)
		{
			if (ft_memcmp(get_env_name(l->content), name,
					ft_strlen(name) + 1) == 0)
				return (prev);
			prev = l;
			l = l->next;
		}
	}
	return (0);
}

static void	del_unset(char *name, t_list *prev)
{
	t_list	*tmp;

	if (ft_memcmp(name, get_env_name(prev->next->content),
			ft_strlen(name) + 1) == 0)
	{
		tmp = prev->next;
		prev->next = prev->next->next;
		ft_lstdelone(tmp, del_env);
	}
}

int	ft_unset(t_cmdtab *c)
{
	t_list	*l1;
	t_list	*prev;
	char	*name;

	if (c->m->env_list && c && c->arg_list)
	{
		l1 = c->arg_list;
		while (l1)
		{
			name = get_arg_value(l1->content);
			if (!is_syntax_ok(name))
				print_error("shell: unset", name, 0, "not a valid identifier");
			prev = find_name_from_env(c->m->env_list, name);
			if (prev)
				del_unset(name, prev);
			l1 = l1->next;
		}
	}
	return (SUCCESS);
}
