/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_quote_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:24:35 by iren              #+#    #+#             */
/*   Updated: 2022/06/24 22:02:35 by gufestin         ###   ########.fr       */
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
	t_quote	*f;

	f = (t_quote *)o;
	free(f);
}
