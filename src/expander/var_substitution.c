/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_substitution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 12:23:51 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/25 00:20:22 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	update_index_value(char *s, int index)
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

char	*join_with_dollar(char *name, char *prev_res)
{
	char	*res;
	char	*tmp;

	tmp = ft_strjoin("$", name);
	if (!tmp)
		exit(1);
	res = ft_strjoin(prev_res, tmp);
	if (!res)
		exit(1);
	free(tmp);
	return (res);
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

void	init_cmd_sub(t_func_cmd_sub *f, t_list *l)
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

char	*join_str_in_list(t_func_cmd_sub *f, char *s, int i)
{
	char	*res;

	res = ft_strjoin(f->res, f->tenv_value);
	free(f->res);
	f->start = f->end + len_word(&s[i]) + 1;
	return (res);
}

char	*little_str_is_not_found(t_func_cmd_sub *f, char *s, int i)
{
	char	*res;
	char	*name;
	char	*p;
	char	q;

	res = 0;
	q = 0;
	if (s)
	{
		if (f->quote_list)
			q = get_quote_char(ft_lstlast(f->quote_list)->content);
		name = ft_substr(s, i + 1, len_word(&s[i]));
		if (q == '"' || q == 0)
		{
			p = ft_getenv(name, f->env_list);
			if (p)
			{
				res = ft_strjoin(f->res, p);
				f->start = f->end + len_word(&s[i]) + 1;
			}
			else
			{
				res = ft_strjoin(f->res, "");
				f->start = f->end + len_word(&s[i]) + 1;
			}
		}
		else
		{
			res = join_with_dollar(name, f->res);
			f->start = f->end + len_word(&s[i]) + 1;
		}
		free(name);
		free(f->res);
	}
	return (res);
}

void	pop1(t_list **l, char *s, int *index_close)
{
	t_list	*tmp;
	int		index_open;
	int		i;

	i = 0;
	tmp = *l;
	index_open = get_quote_index(tmp->content);
	*l = (*l)->next;
	ft_lstdelone(tmp, &del_quote);
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
			if (is_quote(s[i]))
			{
				if (f.quote_list)
				{
					if (matching(get_quote_char(f.quote_list->content), s[i]))
						pop1(&f.quote_list, s, &i);
					else
						push(&f.quote_list, s[i], &s[i], i);
				}
				else
					push(&f.quote_list, s[i], &s[i], i);
			}
			if (s[i] == '$')
			{
				f.res = join_regular_str(&f, i, s);
				if (s[i + 1] == '\0' || ft_isspace(s[i + 1]))
					f.start += ft_strlen(f.res);
				else if (s[i + 1] == '?')
				{
					tmp = f.res;
					tmp2 = ft_itoa(g_errno);
					f.res = ft_strjoin(tmp, tmp2);
					i += 1;
					f.start += ft_strlen(f.res) + 1 ;
					free(tmp);
					free(tmp2);
				}
				else if (check_if_substitution(&s[i], &f))
					f.res = join_str_in_list(&f, s, i);
				else
					f.res = little_str_is_not_found(&f, s, i);
			}
			i++;
		}
	}
	f.res = join_regular_str(&f, i, s);
	ft_lstclear(&f.quote_list, &del_quote);
	return (f.res);
}
