/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:02:11 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/21 01:00:47 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_export(t_mini *m)
{
	int	i;
	int	index;
	char	*p;
	t_list	*new;
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
			new = ft_lstnew(e);
			if (new && is_syntax_ok(e))
				ft_lstadd_back(&m->env_list, new);
			else if (e)
			{
				printf(" export: `%s=%s': not a valid identifier\n", e->name, e->value);
				return (FAILURE);
			}

			p++;
		}
		else
			break ;
	}
	}
	return (SUCCESS);
}
