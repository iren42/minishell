/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_quotes_closed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:53:25 by iren              #+#    #+#             */
/*   Updated: 2022/06/24 23:59:54 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	case_double(char *s, int *i, int len, int *dquote_closed)
{
	(*i)++;
	*dquote_closed = 0;
	if (*i < len)
	{
		while (s[*i] && s[*i] != '"')
		{
			(*i)++;
		}
		if (s[*i] == '"')
			*dquote_closed = 1;
	}
}

static void	case_simple(char *s, int *i, int len, int *squote_closed)
{
	*squote_closed = 0;
	(*i)++;
	if (*i < len)
	{
		while (s[*i] && s[*i] != '\'')
		{
			(*i)++;
		}
		if (s[*i] == '\'')
			*squote_closed = 1;
	}
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
				case_double(s, &i, len, &dquote_closed);
			if (s[i] == '\'')
				case_simple(s, &i, len, &dquote_closed);
			i++;
		}
	}
	if (squote_closed == 1 && dquote_closed == 1)
		return (1);
	return (0);
}
