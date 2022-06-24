/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_superflous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:24:36 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/24 22:36:55 by gufestin         ###   ########.fr       */
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

void	pop(t_list **l, char *s, int *index_close)
{
	t_list	*tmp;
	int		index_open;
	int		i;
	int		metacharacter;

	i = 0;
	metacharacter = 0;
	tmp = *l;
	*l = (*l)->next;
	ft_lstdelone(tmp, &del_quote);
}

int	are_quotes_closed(char *s)
{
	int		i;
	size_t	len;
	int		dquote_closed;
	int		squote_closed;

	i = 0;
	len = ft_strlen(s);
	dquote_closed = 1;
	squote_closed = 1;
	if (s)
	{
		while (i < len)
		{
			if (s[i] == '"')
			{
				i++;
				dquote_closed = 0;
				if (i < len)
				{
					while (s[i] && s[i] != '"')
					{
						i++;
					}
					if (s[i] == '"')
						dquote_closed = 1;
				}
			}
			if (s[i] == '\'')
			{
				squote_closed = 0;
				i++;
				if (i < len)
				{
					while (s[i] && s[i] != '\'')
					{
						i++;
					}
					if (s[i] == '\'')
						squote_closed = 1;
				}
			}
			i++;
		}
	}
	if (squote_closed == 1 && dquote_closed == 1)
		return (1);
	return (0);
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
			{
				start = i++;
				while (s[i] && s[i] != '"')
				{
					if (ft_strchr(" <>$|\n\'", s[i]))
						meta = 1;
					i++;
				}
				if (meta == 0)
				{
					ft_memmove(&s[i], &s[i + 1], ft_strlen(s) + 1);
					ft_memmove(&s[start], &s[start + 1], ft_strlen(s) + 1);
					i -= 2;
				}
			}
			i++;
		}
	}
	return (s);
}
