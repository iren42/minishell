/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redir_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:29:58 by iren              #+#    #+#             */
/*   Updated: 2022/06/24 22:00:17 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_redir(void *o)
{
	t_redir	*r;

	r = (t_redir *)o;
	free(r->filename);
	free(r);
}

t_redir_type	get_redir_type(t_redir *r)
{
	return (r->type);
}
