/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 22:32:17 by iren              #+#    #+#             */
/*   Updated: 2022/06/24 23:03:36 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_pipe_nl(char *p, int *to_set, t_mini *m)
{
	int		start;
	t_token	*t;
	int		len;

	t = malloc(sizeof(t_token));
	if (!t)
		exit(1);
	if (p)
	{
		t->m = m;
		if (p[0] == '|')
			t->type = PIPE;
		else
			t->type = NL;
		t->value = 0;
		*to_set += 1;
	}
	return (t);
}

t_token	*create_token(char *p, int *to_set, t_mini *m)
{
	if (p)
	{
		if (*p == '>')
		{
			if (*(p + 1) == '>')
				return (token_double_great_less(p, to_set, m));
			else
				return (token_great_less(p, to_set, m));
		}
		else if (*p == '<')
		{
			if (*(p + 1) == '<')
				return (token_double_great_less(p, to_set, m));
			else
				return (token_great_less(p, to_set, m));
		}
		else if (*p == '|')
			return (token_pipe_nl(p, to_set, m));
		else if (*p == '\n')
			return (token_pipe_nl(p, to_set, m));
		else
			return (token_word(p, to_set, m));
	}
}
