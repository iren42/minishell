/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:29:57 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/16 23:11:08 by isabelle         ###   ########.fr       */
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

void	init_texport(t_export *e)
{
	e->value = 0;
	e->name = 0;
	e->index = 0;
	e->is_in_quotes = 0;
}

t_export	*create_texport(char *s)
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
	init_texport(e);
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
	return (e);
}

t_list	*create_list(char *s)
{
	int	i;
	t_list	*l;
	char	*p;
	t_list	*new;

	i = 0;
	l = 0;
	p = 0;
	while (s[i])
	{
		p = ft_strnstr(&s[i], "export ", ft_strlen(&s[i]));
		if (p)
		{
			new = ft_lstnew(create_texport(p));
			ft_lstadd_back(&l, new);
			i += 7;
		}
		else
			break ;
		i++;
	}
	return (l);
}

char	*expander(char *s)
{
	char	*res;
	t_list	*export_list;

	export_list = create_list(s);
	print_list(export_list, print_export);
	//	shell_parameter_exp(s);
	return (res);
}
