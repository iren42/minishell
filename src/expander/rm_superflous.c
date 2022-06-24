/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_superflous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:24:36 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/25 00:09:19 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	matching(char b1, char b2)
{
	if (b1 == '"' && b2 == '"')
		return (1);
	if (b1 == '\'' && b2 == '\'')
		return (1);
	return (0);
}

void	push(t_list **l, char c, char *s, int i)
{
	t_quote	*new;
	t_list	*a;

	new = malloc(sizeof(*new));
	new->c = c;
	new->index = i;
	a = ft_lstnew(new);
	ft_lstadd_front(l, a);
}

static void	case_double(char *s, int *i, int *meta, int *start)
{
	*start = (*i)++;
	while (s[*i] && s[*i] != '"')
	{
		if (ft_strchr(" <>$|\n\'", s[*i]))
			*meta = 1;
		(*i)++;
	}
	if (*meta == 0)
	{
		ft_memmove(&s[*i], &s[*i + 1], ft_strlen(s) + 1);
		ft_memmove(&s[*start], &s[*start + 1], ft_strlen(s) + 1);
		*i -= 2;
	}
}

char	*rm_superflous(char *s)
{
	int		i;
	int		start;
	int		meta;
	t_list	*quote_list;

	i = 0;
	quote_list = 0;
	meta = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] == '\'')
			{
				i++;
				while (s[i] && s[i] != '\'')
					i++;
			}
			else if (s[i] == '"')
				case_double(s, &i, &meta, &start);
			i++;
		}
	}
	return (s);
}
