/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:28:11 by iren              #+#    #+#             */
/*   Updated: 2022/06/24 21:59:55 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_token(void *token)
{
	t_token	*t;

	t = (t_token *) token;
	free(t->value);
	free(token);
}

int	get_token_type(t_token *t)
{
	if (t)
		return (t->type);
	return (0);
}

char	*get_token_value(t_token *t)
{
	if (t)
		return (t->value);
	return (0);
}
