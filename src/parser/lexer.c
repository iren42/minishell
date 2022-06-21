/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:42:06 by iren              #+#    #+#             */
/*   Updated: 2022/06/21 16:26:56 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*get_tokenvalue(char *s, int *to_set)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	value = 0;
	if (ft_strchr(";|\n", s[j]))
	{
		value = (0);
		i++;
	}
	else
	{
		if (ft_strchr("<>", s[i]))
			j++;
		if (s[j] == '>')
			j++;
		while (ft_isspace(s[j]))
			j++;
		while (s[i + j] && !is_spe_char(s[i + j]) && !ft_isspace(s[i + j]))
		{
			i++;
		}
		value = malloc(sizeof(char) * (i + 1));
		value = ft_memmove(value, &s[j], i);
		value[i] = 0;
	}
	//	printf("value %s. i %d, j %d\n", value, i, j);
	*to_set += i + j;
	return (value);
}

void	init_token(t_token *t, t_mini *m)
{
	t->type = 0;
	t->value = 0;
	t->m = m;
}

t_token	*create_token(char *p, int *to_set, t_mini *m)
{
	t_token	*t;

	t = malloc(sizeof(t_token));
	if (!t)
		exit(1);
	init_token(t, m);
	if (*p == '>')
	{
		if (*(p + 1) == '>')
			t->type = DOUBLE_GREAT;
		else
			t->type = GREAT;	

	}
	else if (*p == '<')
		t->type = LESS;
	else if (*p == ';')
		t->type = SEMI;
	else if (*p == '|')
		t->type = PIPE;
	else if (*p == '\n')
		t->type = NL;
	else
		t->type = WORD;
	t->value = get_tokenvalue(p, to_set);
	return (t);
}


void create_token_list(char *s, t_list **l, t_mini *m)
{
	int		i;
	t_list	*new;

	i = 0;
	if (s)
	{
	while (s[i])
	{
		if (!ft_isspace(s[i]))
		{
			//	printf("&s[i] %s\n", &s[i]);
			new = ft_lstnew(create_token(&s[i], &i, m));
			ft_lstadd_back(l, new);

		}
		else
			i++;
	}
	new = ft_lstnew(create_token("\n", &i, m));
	ft_lstadd_back(l, new);
	}
}

t_list	*lexer(t_mini *m)
{
	t_list	*l;

	l = 0;
	create_token_list(m->s, &l, m);
	//	print_lst(l);
	return (l);
}
