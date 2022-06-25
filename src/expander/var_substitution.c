/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_substitution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 12:23:51 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/25 02:32:13 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_index_value(char *s, int index)
{
	int	i;

	i = 0;
	if (s)
	{
		if (s[i] == 'e')
		{
			if (ft_strncmp(s, "export ", 7) == 0)
				index++;
		}
	}
	return (index);
}

char	*join_regular_str(t_func_cmd_sub *f, int i, char *s)
{
	char	*res;
	char	*buf;

	res = 0;
	f->end = i;
	if (f->start < f->end)
	{
		buf = ft_substr(s, f->start, f->end - f->start);
		res = ft_strjoin(f->res, buf);
		free(buf);
		free(f->res);
		return (res);
	}
	return (f->res);
}

static void	init_cmd_sub(t_func_cmd_sub *f, t_list *l)
{
	f->env_list = l;
	f->start = 0;
	f->end = 0;
	f->tenv_value = 0;
	f->quote_list = 0;
	f->list_index = -1;
	f->res = ft_strdup("");
	if (!f->res)
		exit(1);
}

char	*var_substitution(t_list *list, char *s)
{
	t_func_cmd_sub	f;
	int				i;
	char			*tmp;
	char			*tmp2;

	init_cmd_sub(&f, list);
	i = 0;
	if (s)
	{
		while (s[i])
		{
			f.list_index = update_index_value(&s[i], f.list_index);
			sub_for_quotes(&f, &i, s);
			sub_dollar(&f, &i, s);
			i++;
		}
	}
	f.res = join_regular_str(&f, i, s);
	ft_lstclear(&f.quote_list, &del_quote);
	return (f.res);
}
