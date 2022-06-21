/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arg_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:28:49 by iren              #+#    #+#             */
/*   Updated: 2022/06/21 16:35:23 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_arg_value(void *o)
{
	t_arg	*a;

	a = (t_arg *)o;
	return (a->value);
}
void	del_arg(void *o)
{
	t_arg *a;

	a = (t_arg *)o;
	free(a->value);
	free(a);
}
