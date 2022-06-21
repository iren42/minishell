/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:02:11 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/21 10:48:30 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_name(void *o)
{
	t_env	*e;
	e = (t_env *)o;
	//	printf("env name %s\n", e->name);
	return (e->name);
}
char	*get_env_value(void *o)
{
	t_env	*e;
	e = (t_env *)o;
	return (e->value);
}
void	separate_name_value(t_env *e, char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
	{
		i++;
	}
	//	printf("s[i] %c, i %d\n", s[i], i);
}

void	init_tenv(t_env *e)
{
	e->value = 0;
	e->name = 0;
}

t_env	*create_tenv(t_arg *a)
{
	int	len;
	t_env	*e;

	e = malloc(sizeof(t_env));
	if (!e)
		exit(1);
	init_tenv(e);
	len = get_len_env_name(a->value);
	e->name = ft_substr(a->value, 0, len);
	e->value = ft_substr(a->value, len + 1, ft_strlen(a->value));

	//	printf("get export value %s\n", s);
	return (e);
}

int	is_syntax_ok(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		//	printf("%c %d %d\n", s[i], ft_isalnum(s[i]), ft_isdigit(s[i]));
		if (!ft_isalnum(s[i]) && !ft_isdigit(s[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	add_in_list_or_replace(t_mini *m, t_env *e)
{
	t_list	*l;
	t_list	*new;
	t_list	*prev;
	int	add;

	add = 0;
	l = m->env_list;
	if (e)
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
