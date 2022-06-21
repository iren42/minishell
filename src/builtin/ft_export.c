/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:02:11 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/21 02:14:23 by iren             ###   ########.fr       */
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
	e->name = ft_substr(s, 0, i);
	e->value = ft_substr(s, i + 1, ft_strlen(s));
}

void	init_tenv(t_env *e, int index)
{
	e->value = 0;
	e->name = 0;
	e->index = index;
}

t_env	*create_tenv(char *s, int index)
{
	int	i;
	t_env	*e;
	char	q;
	char	*namevalue;

	i = 0;
	s += 7;
	q = 0;
	e = malloc(sizeof(t_env));
	if (!e)
		exit(1);
	init_tenv(e, index);
	//	printf("get export value %s\n", s);
	if (is_quote(s[i]))
	{
		q = s[i++];
		while (s[i] && q)
		{
			if (s[i] == q)
				break;
			i++;
		}
	}
	else
	{
		while (s[i])
		{
			if (ft_strchr(";|\t\v\n\f\r ", s[i]))
				break;
			i++;
		}
	}
	namevalue = ft_substr(s, 0, i);
	separate_name_value(e, namevalue);
	free(namevalue);
	return (e);
}

int	is_syntax_ok(t_env *e)
{
	int	i;

	i = 0;
	while (e->name[i])
	{
		//	printf("%c %d %d\n", e->name[i], ft_isalnum(e->name[i]), ft_isdigit(e->name[i]));
		if (!ft_isalnum(e->name[i]) && !ft_isdigit(e->name[i]))
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

int	ft_export(t_mini *m)
{
	int	i;
	int	index;
	char	*p;
	t_env	*e;
	char	*s;

	i = 0;
	s = m->s;
	index = 0;
	p = m->s;
	if (s)
	{
		while (s[i])
		{
			p = ft_strnstr(p, "export ", ft_strlen(p));
			if (p)
			{
				//			printf("i %d, p %s\n", i, p);
				e = create_tenv(p, index++);
				if (e && is_syntax_ok(e))
					add_in_list_or_replace(m, e);
				else if (e)
				{
					printf(" export: `%s=%s': not a valid identifier\n", e->name, e->value);
					return (FAILURE);
				}
				else
					return (FAILURE);
				p++;
			}
			else
				break ;
		}
	}
	return (SUCCESS);
}
