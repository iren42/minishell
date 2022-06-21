/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:37:30 by iren              #+#    #+#             */
/*   Updated: 2022/06/21 17:14:14 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_old(t_list *env_list)
{
	char	*path_old;


	return (SUCCESS);
}
int	ft_cd(t_cmdtab *c)
{

int		err;
	char	*path;

	if (c->arg_list == 0)
		path = ft_getenv("HOME", c->m->env_list);
	else if (ft_lstsize(c->arg_list) > 2)
	{
		print_error("shell: cd", NULL, 0, "Too many arguments");
		return (FAILURE);
	}
	else
	{
		path = get_arg_value(c->arg_list->content);
		printf("path %s\n", path);
	}
	if (chdir(path))
		print_error("shell: cd", path, errno, "No such file or directory");

		return (SUCCESS);
}
