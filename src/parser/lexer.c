/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:42:06 by iren              #+#    #+#             */
/*   Updated: 2022/06/25 02:06:31 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_error_token(t_list **l)
{
	print_error("shell", 0, errno, "syntax error lexer");
	ft_lstclear(l, del_token);
	return (FAILURE);
}

static int	inside_loop(char *s, int *i, t_mini *m, t_list **l)
{
	t_list	*new;
	t_token	*t;

	if (!ft_isspace(s[*i]))
	{
		t = create_token(&s[*i], i, m);
		if (!t)
			return (syntax_error_token(l));
		new = ft_lstnew(t);
		ft_lstadd_back(l, new);
	}
	else
		(*i)++;
	return (SUCCESS);
}

static int	create_token_list(char *s, t_list **l, t_mini *m)
{
	int		i;
	t_list	*new;
	int		len;
	t_token	*t;

	i = 0;
	if (s)
	{
		len = ft_strlen(s);
		while (i < len)
		{
			if (inside_loop(s, &i, m, l) == FAILURE)
				return (FAILURE);
		}
		new = ft_lstnew(create_token("\n", &i, m));
		ft_lstadd_back(l, new);
	}
	return (SUCCESS);
}

int	lexer(t_mini *m)
{
	t_list	*l;
	int		ret;

	l = 0;
	ret = create_token_list(m->s, &l, m);
	if (ret == SUCCESS)
	{
		ret = check_syntax_token(l);
		m->token_list = l;
	}
	return (ret);
}
