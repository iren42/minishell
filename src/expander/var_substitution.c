/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_substitution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 12:23:51 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/24 21:40:27 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	check_if_substitution(char *s, t_func_cmd_sub *f)
{
	t_list	*l;
	char	*name;
	int	index;
	char	q;

	if (f->quote_list != 0)
	{
		//		printf("ccc %c\n", get_quote_char(ft_lstlast(f->quote_list)->content));
		q = get_quote_char(ft_lstlast(f->quote_list)->content);
		if (q == '\'')
			return (0);
	}
	l = f->env_list;
	name = str_tenvname(s);
	//	printf("name %s\n", name);
	if (!name)
		exit(1);
	while (l)
	{
		//		printf("name %s, get name %s\n", name, get_env_name(l->content));
		if (ft_memcmp(name, get_env_name(l->content),
					ft_strlen(name) + 1) == 0)
		{
			f->tenv_value = get_env_value(l->content);
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

	//	printf("HERE\n");
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
				//	res = join_with_dollar(name, f->res);
				res = ft_strjoin(f->res, "");	
				f->start = f->end + len_word(&s[i]) + 1;
			}
		}
		else
		{
			res = join_with_dollar(name, f->res);
			//		res = ft_strjoin(f->res, "");	
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
	index_open = get_quote_index(tmp->content);
	*l = (*l)->next;
	ft_lstdelone(tmp, &del_quote);
}
char	*var_substitution(t_list *list, char *s)
{
	t_func_cmd_sub	f;
	int	i;
	char	*tmp;
	char	*tmp2;

	init_cmd_sub(&f, list);
	i = 0;
	if (s)
	{
		while (s[i])
		{ // liste des quotes, pour savoir si on doit faire une var subs
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
				printf("after regular str %s.\n", f.res);
				if (s[i + 1] == '\0' || ft_isspace(s[i + 1]))
					f.start += ft_strlen(f.res);
				else if (s[i + 1] == '?')
				{
					printf("i %d\n", i);
					tmp = f.res;
					printf("f.res = %s.\n", f.res); // echo
					tmp2 = ft_itoa(g_errno);
					f.res = ft_strjoin(tmp, tmp2);
					printf("f.res 2 = %s.\n", f.res); // echo 0
					i += 1; 
					printf("g errno %d\n", g_errno);
					f.start += ft_strlen(f.res) + 1 ;
					printf("i %d\n", i);
					free(tmp);
					free(tmp2);
				}

				else if (check_if_substitution(&s[i], &f))
				{
					f.res = join_str_in_list(&f, s, i);
					//				printf("is in list\n");
				}
				else
				{
					f.res = little_str_is_not_found(&f, s, i);
					//				printf("env not found\n");
				}
			}
			i++;
		}
		//	i++;
	}
	f.res = join_regular_str(&f, i, s);
	ft_lstclear(&f.quote_list, &del_quote);
			printf("var_sub() final s %s\n", f.res);
	return (f.res);
}


