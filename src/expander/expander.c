/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:29:57 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/23 09:36:48 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*expander(t_mini *m)
{
	char	*res;

//	printf("expander before rm superflous %s\n", m->s);
	m->s = rm_superflous(m->s);
//	printf("expander after rm superflous %s\n", m->s);
//	create_list(m);
//		print_list(m->env_list, print_env);
		
	res = var_substitution(m->env_list, m->s);
//	ft_lstclear(&env_list, del_tenv);
//	printf("expander after var subtitution s :%s|\n", res);
//	free(res);
	return (res);
}
