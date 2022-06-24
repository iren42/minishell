/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:29:57 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/24 22:30:43 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expander(t_mini *m)
{
	char	*res;
	int		ret;

	ret = are_quotes_closed(m->s);
	if (ret)
	{
		m->s = rm_superflous(m->s);
		res = var_substitution(m->env_list, m->s);
		if (!res)
			exit(0);
		res = rm_superflous(res);
		free(m->s);
		m->s = res;
	}
	else
		free(m->s);
	return (ret);
}
