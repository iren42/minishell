/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_for_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 01:22:18 by iren              #+#    #+#             */
/*   Updated: 2022/06/25 01:24:04 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pop1(t_list **l, char *s, int *index_close)
{
	t_list	*tmp;
	int		index_open;
	int		i;

	i = 0;
	tmp = *l;
	index_open = get_quote_index(tmp->content);
	*l = (*l)->next;
	ft_lstdelone(tmp, &del_quote);
}

void	sub_for_quotes(t_func_cmd_sub *f, int *i, char *s)
{
	if (is_quote(s[*i]))
	{
		if (f->quote_list)
		{
			if (matching(get_quote_char(f->quote_list->content), s[*i]))
				pop1(&f->quote_list, s, i);
			else
				push(&f->quote_list, s[*i], &s[*i], *i);
		}
		else
			push(&f->quote_list, s[*i], &s[*i], *i);
	}
}
