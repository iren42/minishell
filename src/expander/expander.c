/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:29:57 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/19 22:49:29 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	del_texport(void *o)
{
	t_export	*e;

	e = (t_export *)o;
	free(e->name);
	free(e->value);
	free(e);
}

char	*expander(char *s)
{
	char	*res;
	t_list	*export_list;

	s = rm_superflous(s);
	export_list = create_list(s);
		print_list(export_list, print_export);
	res = var_substitution(export_list, s);
	ft_lstclear(&export_list, del_texport);
//	printf("final res %s|\n", res);
//	free(res);
	return (res);
}
