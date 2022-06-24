/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 01:08:39 by iren              #+#    #+#             */
/*   Updated: 2022/06/25 01:20:28 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_str_in_list(t_func_cmd_sub *f, char *s, int i)
{
	char	*res;

	res = ft_strjoin(f->res, f->tenv_value);
	free(f->res);
	f->start = f->end + len_word(&s[i]) + 1;
	return (res);
}

static char	*join_with_dollar(char *name, char *prev_res)
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

static char	*search_in_env(char *p, t_func_cmd_sub *f, char *s, char *name)

{
	char	*res;

	p = ft_getenv(name, f->env_list);
	if (p)
	{
		res = ft_strjoin(f->res, p);
		f->start = f->end + len_word(s) + 1;
	}
	else
	{
		res = ft_strjoin(f->res, "");
		f->start = f->end + len_word(s) + 1;
	}
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
			res = search_in_env(p, f, &s[i], name);
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

void	sub_dollar(t_func_cmd_sub *f, int *i, char *s)
{
	char			*tmp;
	char			*tmp2;

	if (s[*i] == '$')
	{
		f->res = join_regular_str(f, *i, s);
		if (s[*i + 1] == '\0' || ft_isspace(s[*i + 1]))
			f->start += ft_strlen(f->res);
		else if (s[*i + 1] == '?')
		{
			tmp = f->res;
			tmp2 = ft_itoa(g_errno);
			f->res = ft_strjoin(tmp, tmp2);
			*i += 1;
			f->start += ft_strlen(f->res) + 1 ;
			free(tmp);
			free(tmp2);
		}
		else if (check_if_substitution(&s[*i], f))
			f->res = join_str_in_list(f, s, *i);
		else
			f->res = little_str_is_not_found(f, s, *i);
	}
}
