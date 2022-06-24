/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmdtab_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:29:20 by iren              #+#    #+#             */
/*   Updated: 2022/06/24 22:04:31 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_cmdtab(void *o)
{
	t_cmdtab	*c;

	c = (t_cmdtab *)o;
	free(c->cmd);
	ft_lstclear(&c->arg_list, del_arg);
	ft_lstclear(&c->redir_list, del_redir);
	free(c);
}

t_cmdtab	*get_cmdtab_ptr(void *o)
{
	t_cmdtab	*c;

	c = (t_cmdtab *)o;
	return (c);
}
