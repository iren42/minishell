/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:02:11 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/21 20:02:05 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	add_in_list_or_replace(t_mini *m, t_env *e)
{
	t_list	*l;
	t_list	*new;
	t_list	*prev;
	int	add;

	add = 0;
	l = m->env_list;
	if (e && l)
	{
		while (l)
		{
			if (ft_memcmp(get_env_name(l->content), e->name, ft_strlen(e->name) + 1) == 0)
			{
				// replace
				prev->next = l->next;
				ft_lstdelone(l, del_env);
				new = ft_lstnew(e);
				ft_lstadd_back(&m->env_list, new);
				add = 1;
				break ;
			}
			prev = l;
			l = l->next;
		}
		if (add == 0)
		{
			new = ft_lstnew(e);
			ft_lstadd_back(&m->env_list, new);
		}
	}
}

int	ft_export(t_cmdtab *c)
{
	char	*p;
	t_list	*l;
	t_env	*e;

	if (c)
	{
		l = c->arg_list;
		while (l)
		{
			//			printf("i %d, p %s\n", i, p);
			e = create_tenv(l->content);
			if (e && is_syntax_ok(e->name))
				add_in_list_or_replace(c->m, e);
			else if (e)
			{
				printf(" export: `%s=%s': not a valid identifier\n", e->name, e->value);
				return (FAILURE);
			}
			else
				return (FAILURE);
			l = l->next;	
		}
	}
	return (SUCCESS);
}
