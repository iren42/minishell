/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:29:57 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/20 20:53:17 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	del_tenv(void *o)
{
	t_env	*e;

	e = (t_env *)o;
	free(e->name);
	free(e->value);
	free(e);
}

char	*expander(char *s)
{
	char	*res;
	t_list	*env_list;

	s = rm_superflous(s);
	env_list = create_list(s);
//		print_list(env_list, print_env);
	res = var_substitution(env_list, s);
	ft_lstclear(&env_list, del_tenv);
//	printf("final res %s|\n", res);
//	free(res);
	return (res);
}
