/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:29:57 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/21 16:23:53 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*expander(t_mini *m)
{
	char	*res;

	m->s = rm_superflous(m->s);
//	create_list(m);
//		print_list(m->env_list, print_env);
		
	res = var_substitution(m->env_list, m->s);
//	ft_lstclear(&env_list, del_tenv);
//	printf("final res %s|\n", res);
//	free(res);
	return (res);
}
