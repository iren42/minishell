/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_quote_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:24:35 by iren              #+#    #+#             */
/*   Updated: 2022/06/21 16:25:56 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_quote_index(void *o)
{
	t_quote	*f;

	f = (t_quote *)o;
	return (f->index);

}


char	get_quote_char(void *o)
{
	t_quote	*f;

	f = (t_quote *)o;
	return (f->c);
}

void	del_quote(void *o)
{
	t_quote *f;
	f = (t_quote *)o;
	free(f);
}


void	print_quote(void *o)
{
	t_quote *f;

	f = (t_quote *)o;
	printf("q index %d\n", f->index);
	printf("q c %c\n", f->c);
}


