/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_substitution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 12:23:51 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/20 19:40:53 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name_e(t_env *e)
{
	return (e->name);
}

char	*get_value_e(t_env *e)
{
	return (e->value);
}

int	len_word(char *s)
{
	int	i;
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
		{
			while (s[i])
			{
				if (ft_strchr(" |<>'\"", s[i]))
				{
					i--;
					break;
				}
				i++;
			}
		}
	}
	return (i);
}

char	*str_tenvname(char *s)
{
	char	*name;
	int	len_w;

	len_w = len_word(s);
	name = malloc(sizeof(char) * (len_w + 1));
	if (!name)
		return (0);
	name = ft_memmove(name, ++s, len_w);
	name[len_w] = '\0';
	return (name);
}

int	little_str_in_list(char *s, t_func_cmd_sub *f)
{
	t_list	*l;
	char	*name;
	int	index;
	char	q;

	if (f->quote_list != 0)
	{
		//		printf("ccc %c\n", get_char(ft_lstlast(f->quote_list)->content));
		q = get_char(ft_lstlast(f->quote_list)->content);
		if (q == '\'')
			return (0);
	}
	l = f->l;
	index = f->list_index;
	name = str_tenvname(s);
	//	printf("name %s\n", name);
	if (!name)
		exit(1);
	while (index-- >= 0)
	{
		//		printf("name %s, get name %s\n", name, get_name_e(l->content));
		if (ft_strncmp(name, get_name_e(l->content),
					ft_strlen(name)) == 0)
		{
			f->tenv_value = get_value_e(l->content);
			free(name);
			return (1);
		}
		l = l->next;
	}
	free(name);
	return (0);
}

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

	//	printf("join with dollar() name %s\n", name);
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
	f->l = l;
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

	//			printf("buff %s|\n", buff);
	res = ft_strjoin(f->res, f->tenv_value);
	free(f->res);
	f->start = f->end + len_word(&s[i]) + 1;
	return (res);

}

char	*little_str_is_in_env_or_not(t_func_cmd_sub *f, char *s, int i)
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
			q = get_char(ft_lstlast(f->quote_list)->content);

		name = ft_substr(s, i + 1, len_word(&s[i]));
		if (q == '"' || q == 0)
		{
			p = getenv(name);
			if (p)
			{
				res = ft_strjoin(f->res, p);
				f->start = f->end + len_word(&s[i]) + 1;
			}
			else
			{
				res = join_with_dollar(name, f->res);
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

void pop1(t_list **l, char *s, int *index_close)
{
	t_list	*tmp;
	int	index_open;
	int	i;

	i = 0;
	tmp = *l;
	index_open = get_index(tmp->content);
	*l = (*l)->next;
	ft_lstdelone(tmp, &del_tfunc_rm_quotes);
}

void	print_quote(void *o)
{
	t_quote *f;

	f = (t_quote *)o;
	printf("q index %d\n", f->index);
	printf("q c %c\n", f->c);
}

char	*var_substitution(t_list *list, char *s)
{
	t_func_cmd_sub	f;
	int	i;

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
				if (matching(get_char(f.quote_list->content), s[i]))
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
			if (little_str_in_list(&s[i], &f))
				f.res = join_str_in_list(&f, s, i);
			else
				f.res = little_str_is_in_env_or_not(&f, s, i);
		}
		i++;
	}
	f.res = join_regular_str(&f, i, s);
	ft_lstclear(&f.quote_list, &del_tfunc_rm_quotes);
	//	printf("var_sub() final s %s\n", f.res);
	}
	return (f.res);
}
