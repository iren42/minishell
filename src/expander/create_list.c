/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:02:11 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/18 14:42:13 by isabelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	separate_name_value(t_export *e, char *s)
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

void	init_texport(t_export *e, int index)
{
	e->value = 0;
	e->name = 0;
	e->index = index;
	e->is_in_quotes = 0;
}

t_export	*create_texport(char *s, int index)
{
	int	i;
	t_export	*e;
	char	q;
	char	*namevalue;

	i = 0;
	s += 7;
	q = 0;
	e = malloc(sizeof(t_export));
	if (!e)
		exit(1);
	init_texport(e, index);
	//	printf("get export value %s\n", s);
	if (is_quote(s[i]))
	{
		e->is_in_quotes = 1;
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
			if (ft_strchr(";|\n ", s[i]))
				break;
			i++;
		}
	}
	namevalue = ft_substr(s, 0, i);
	separate_name_value(e, namevalue);
	free(namevalue);
	return (e);
}

t_list	*create_list(char *s)
{
	int	i;
	int	index;
	t_list	*l;
	char	*p;
	t_list	*new;

	i = 0;
	l = 0;
	index = 0;
	p = s;
	while (s[i])
	{
		p = ft_strnstr(p, "export ", ft_strlen(p));
		if (p)
		{
			printf("i %d, p %s\n", i, p);
			new = ft_lstnew(create_texport(p, index++));
			ft_lstadd_back(&l, new);
			p++;
		}
		else
			break ;
	}
	return (l);
}
