/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:29:57 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/18 14:44:16 by isabelle         ###   ########.fr       */
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

	export_list = create_list(s);
	//	print_list(export_list, print_export);
	res = command_substitution(export_list, s);
	ft_lstclear(&export_list, del_texport);
	printf("final res %s|\n", res);
	free(res);
	//	shell_parameter_exp(s);
	return (s);
}
