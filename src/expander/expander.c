/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:29:57 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/24 13:12:38 by iren             ###   ########.fr       */
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
//	printf("in expander after rm superflous %s.\n", m->s);
		
	res = var_substitution(m->env_list, m->s); // malloc
	if (!res)
		exit(0);

	res = rm_superflous(res); // directement sur la string, pas malloc
//	printf("in expander after var subtitution s %s.\n", res);
	m->s = res;
	return (ret);
}
