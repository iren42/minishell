/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:29:57 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/24 12:29:46 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	expander(t_mini *m)
{
	char	*res;
	int	ret;


//	printf("expander before rm superflous %s\n", m->s);
	ret = are_quotes_closed(m->s);
	if (!ret)
		return (0);
	m->s = rm_superflous(m->s); // directement sur la string, pas malloc
	printf("expander after rm superflous %s.\n", m->s);
//	create_list(m);
//		print_list(m->env_list, print_env);
		
	res = var_substitution(m->env_list, m->s);

	res = rm_superflous(res); // directement sur la string, pas malloc
//	ft_lstclear(&env_list, del_tenv);
	printf("expander after var subtitution s %s.\n", res);
//	free(m->s);
	m->s = res;
//	free(res);
	return (ret);
}
