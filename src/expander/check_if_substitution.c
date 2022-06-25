/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_substitution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 00:12:41 by iren              #+#    #+#             */
/*   Updated: 2022/06/25 02:13:07 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	case_wthout_quote(char *s, int *i)
{
	while (s[*i])
	{
		if (ft_strchr(" |<>'\"", s[*i]))
		{
			(*i)--;
			return ;
		}
		(*i)++;
	}
}

int	len_word(char *s)
{
	int		i;
	char	q;

	i = 0;
	if (s)
	{
		q = is_quote(s[i]);
		if (q)
		{
			while (s[i] && s[i] != q)
				i++;
		}
		else
			case_wthout_quote(s, &i);
	}
	return (i);
}

char	*str_tenvname(char *s)
{
	char	*name;
	int		len_w;

	len_w = len_word(s);
	name = malloc(sizeof(char) * (len_w + 1));
	if (!name)
		return (0);
	name = ft_memmove(name, ++s, len_w);
	name[len_w] = '\0';
	return (name);
}

static int	set_value(t_func_cmd_sub *f, t_list *l, char *name)
{
	f->tenv_value = get_env_value(l->content);
	free(name);
	return (1);
}

int	check_if_substitution(char *s, t_func_cmd_sub *f)
{
	t_list	*l;
	char	*name;
	char	q;

	if (f->quote_list != 0)
	{
		q = get_quote_char(ft_lstlast(f->quote_list)->content);
		if (q == '\'')
			return (0);
	}
	l = f->env_list;
	name = str_tenvname(s);
	if (!name)
		exit(1);
	while (l)
	{
		if (ft_memcmp(name, get_env_name(l->content),
				ft_strlen(name) + 1) == 0)
			return (set_value(f, l, name));
		l = l->next;
	}
	free(name);
	return (0);
}
