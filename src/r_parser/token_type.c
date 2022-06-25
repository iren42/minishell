/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:01:26 by iren              #+#    #+#             */
/*   Updated: 2022/06/24 23:05:39 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calc_len_word(int *len, int *start, char *p, t_token *t)
{
	while (p[*len + *start] && !ft_isspace(p[*len + *start])
		&& !is_spe_char(p[*len + *start]))
		(*len)++;
	if (len == 0)
	{
		free(t);
		return (1);
	}
	return (0);
}

static void	set_value(t_token *t, int start, int len, char *p)
{
	t->value = malloc(sizeof(char) * (len + 1));
	if (!t->value)
		exit(1);
	t->value = ft_memmove(t->value, &p[start], len + 1);
	t->value[len] = 0;
}

t_token	*token_double_great_less(char *p, int *to_set, t_mini *m)
{
	int		start;
	t_token	*t;
	int		len;

	if (p)
	{
		t = malloc(sizeof(t_token));
		if (!t)
			return (0);
		t->m = m;
		t->type = DOUBLE_LESS;
		if (p[0] == '>' && p[1] == '>')
			t->type = DOUBLE_GREAT;
		start = 2;
		len = 0;
		while (ft_isspace(p[start]) && p[start])
			start++;
		if (!ft_isspace(p[start]))
			*to_set += calc_len_word(&len, &start, p, t);
		set_value(t, start, len, p);
		*to_set += len + start;
	}
	return (t);
}

t_token	*token_great_less(char *p, int *to_set, t_mini *m)
{
	int		start;
	t_token	*t;
	int		len;

	if (p)
	{
		t = malloc(sizeof(t_token));
		if (!t)
			exit(1);
		t->m = m;
		start = 1;
		if (p[0] == '>')
			t->type = GREAT;
		else
			t->type = LESS;
		len = 0;
		while (ft_isspace(p[start]) && p[start])
			start++;
		if (!ft_isspace(p[start]))
			*to_set += calc_len_word(&len, &start, p, t);
		set_value(t, start, len, p);
		*to_set += len + start;
	}
	return (t);
}

t_token	*token_word(char *p, int *to_set, t_mini *m)
{
	int		start;
	t_token	*t;
	int		len;

	if (p)
	{
		t = malloc(sizeof(t_token));
		if (!t)
			exit(1);
		start = 0;
		t->type = WORD;
		t->m = m;
		len = 0;
		while (ft_isspace(p[start]) && p[start])
			start++;
		if (!ft_isspace(p[start]))
			*to_set += calc_len_word(&len, &start, p, t);
		set_value(t, start, len, p);
		*to_set += len + start;
	}
	return (t);
}
