/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 02:05:58 by gufestin          #+#    #+#             */
/*   Updated: 2022/06/25 02:52:55 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_size_two(t_list *l)
{
	t_list	*prev;

	prev = l;
	while (l->next)
	{
		if (((t_token *)(l->content))->type == PIPE
				&& (((t_token *)(prev->content))->type != WORD
					|| ((t_token *)(l->next->content))->type != WORD))
		{
			print_error("shell", 0, 0, "syntax token");
			return (FAILURE);
		}
		prev = l;
		l = l->next;
	}
	return (SUCCESS);
}

int	check_syntax_token(t_list *tokens)
{
	t_list	*l;
	int		size;

	l = tokens;
	size = ft_lstsize(l);
	if ((((t_token *)(l->content))->type == PIPE))
	{	
		print_error("shell", 0, 0, "syntax token |");
		return (FAILURE);
	}
	if (size == 2 && (((t_token *)(l->next->content))->type == PIPE))
	{
		print_error("shell", 0, 0, "syntax token |");
		return (FAILURE);
	}
	return (check_syntax_size_two(l));
}
