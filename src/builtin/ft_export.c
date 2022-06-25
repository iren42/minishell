/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:02:11 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/25 02:44:55 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace(t_list *l, t_env *e_from_envl, t_env *e, int *add)
{
	e_from_envl = l->content;
	free(e_from_envl->value);
	e_from_envl->value = ft_strdup(e->value);
	if (!e_from_envl)
		exit(1);
	del_env(e);
	*add = 1;
}

static void	ft_add(t_env *e, t_mini *m)
{
	t_list	*new;

	new = ft_lstnew(e);
	ft_lstadd_back(&m->env_list, new);
}

static void	add_in_list_or_replace(t_mini *m, t_env *e)
{
	t_list	*l;
	t_env	*e_from_envl;
	int		add;

	e_from_envl = NULL;
	add = 0;
	l = m->env_list;
	if (e && l)
	{
		while (l)
		{
			if (ft_memcmp(get_env_name(l->content), e->name,
					ft_strlen(e->name) + 1) == 0)
			{
				replace(l, e_from_envl, e, &add);
				break ;
			}
			l = l->next;
		}
		if (add == 0)
			ft_add(e, m);
	}
}

static void	add_repl_tenv(t_env *e, t_cmdtab *c, t_list *l)
{
	if (is_syntax_ok(e->name))
		add_in_list_or_replace(c->m, e);
	else
	{
		print_error("shell: export", get_arg_value(l->content), 0,
			"not a valid identifier");
		del_env(e);
	}
}

int	ft_export(t_cmdtab *c)
{
	t_list	*l;
	t_env	*e;

	if (c)
	{
		l = c->arg_list;
		while (l)
		{
			e = create_tenv(l->content);
			if (e)
				add_repl_tenv(e, c, l);
			else
			{
				if (!is_syntax_ok(get_arg_value(l->content)))
					print_error("shell: export", get_arg_value(l->content), 0,
						"not a valid identifier");
				return (FAILURE);
			}
			l = l->next;
		}
	}
	return (SUCCESS);
}
