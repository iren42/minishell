/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_len_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 05:12:56 by gufestin          #+#    #+#             */
/*   Updated: 2022/06/25 08:12:38 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	double_quote_case(int *len, char *p, int *start, t_token *t)
{
	(*len)++;
	while (p[*len + *start] != '"' && p[*len + *start])
		(*len)++;
	if (p[*len + *start] == '"')
		(*len)++;
	t->is_in_quotes = 1;
}

int	calc_len_word(int *len, int *start, char *p, t_token *t)
{
	if (*p == '"')
		double_quote_case(len, p, start, t);
	else if (*p == '\'')
	{
		(*len)++;
		while (p[*len + *start] != '\'' && p[*len + *start])
			(*len)++;
		if (p[*len + *start] == '\'')
			(*len)++;
		t->is_in_quotes = 1;
	}
	else
	{
		while (p[*len + *start] && !ft_isspace(p[*len + *start])
			&& !is_spe_char(p[*len + *start]))
			(*len)++;
	}
	if (len == 0)
	{
		free(t);
		return (1);
	}
	return (0);
}
