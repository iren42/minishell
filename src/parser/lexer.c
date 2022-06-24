/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:42:06 by iren              #+#    #+#             */
/*   Updated: 2022/06/24 16:21:16 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*get_tokenvalue(char *s, int *to_set)
{
	int		len;
	int		start;
	char	*value;
	char	q;
	int	size;

	value = 0;
	//	printf("get token value s :%s.\n", s);
	if (s)
	{
		len = 0;
		size = ft_strlen(s);
		start = 0;
		q = 0;
		if (ft_strchr("|\n", s[start])) // token for pipe and NL
		{
			len++;
		}
		else
		{
			if (s[start] == '<' && s[start + 1] == '<') // skip <>
				start += 2;
			else if (s[start] == '>' || s[start + 1] == '>') // skip <>
				start += 2;

			//while (ft_isspace(s[start]) && s[start]) // skip spaces
			//	start++;
			if (is_quote(s[start]))
			{
				q = s[start + len++];
				while (s[start + len] && q != s[start + len])
					len++;
				len++;
			}
			else
			{
				//	while (s[len + start] && !ft_isspace(s[len + start]) && !is_spe_char(s[len + start]) && !is_quote(s[len + start]))
				while (s[len + start] && !ft_isspace(s[len + start]) && !is_spe_char(s[len + start]))
					len++;
			}
			//			printf("len %d\n", len);
			if (len == 0)
				return (0);
			value = malloc(sizeof(char) * (len + 1));
			value = ft_memmove(value, &s[start], len + 1);
			value[len] = 0;
		}
		*to_set += len + start;
		//	printf("value %s. len %d, start %d, to_set %d\n", value, len, start, *to_set);
	}
	return (value);
}

void	init_token(t_token *t, t_mini *m)
{
	t->type = 0;
	t->value = 0;
	t->m = m;
}
t_token	*token_double_great_less(char *p, int *to_set, t_mini *m)
{
	int	start;
	t_token	*t;
	int	len;
	t = malloc(sizeof(t_token));
	t->m = m;

	if (p)
	{
		if (p[0] == '>' && p[1] == '>')
			t->type = DOUBLE_GREAT;
		else
			t->type = DOUBLE_LESS;
		start = 2;
		len = 0;
		while (ft_isspace(p[start]) && p[start])
			start++;
		if (!ft_isspace(p[start]))
		{
			while (p[len + start] && !ft_isspace(p[len + start]) && !is_spe_char(p[len + start]))
				len++;
			if (len == 0)
			{
				free(t);
				*to_set += 1;
				//				printf("syntax error token great\n");
				return (0);
			}	

		}
		t->value = malloc(sizeof(char) * (len + 1));
		t->value = ft_memmove(t->value, &p[start], len + 1);
		t->value[len] = 0;
		*to_set += len + start;
	}
	return (t);
}

t_token	*token_great_less(char *p, int *to_set, t_mini *m)
{
	int	start;
	t_token	*t;
	int	len;
	t = malloc(sizeof(t_token));

	if (p)
	{
		t->m = m;
		start = 1;
		if (p[0] == '>')
			t->type = GREAT;
		else
			t->type = LESS;
		len = 0;
		while (ft_isspace(p[start]) && p[start])
			start++;
		if (!ft_isspace(p[start]))
		{
			//			printf("p start %c %d\n", p[start], start);
			while (p[len + start] && !ft_isspace(p[len + start]) && !is_spe_char(p[len + start]))
				len++;
			if (len == 0)
			{
				free(t);
				*to_set += 1;
				//				printf("syntax error token great\n");
				return (0);
			}	

		}
		t->value = malloc(sizeof(char) * (len + 1));
		t->value = ft_memmove(t->value, &p[start], len + 1);
		t->value[len] = 0;
		*to_set += len + start;
	}
	return (t);
}
t_token	*token_pipe_nl(char *p, int *to_set, t_mini *m)
{
	int	start;
	t_token	*t;
	int	len;
	t = malloc(sizeof(t_token));

	if (p)
	{
		t->m = m;
		if (p[0] == '|')
			t->type = PIPE;
		else
			t->type = NL;
		t->value = 0;
		*to_set += 1;
	}
	return (t);
}
t_token	*token_word(char *p, int *to_set, t_mini *m)
{
	int	start;
	t_token	*t;
	int	len;
	t = malloc(sizeof(t_token));

	if (p)
	{
		start = 0;
		t->type = WORD;
		t->m = m;
		len = 0;
		while (ft_isspace(p[start]) && p[start])
			start++;
		if (!ft_isspace(p[start]))
		{
			//			printf("p start %c %d\n", p[start], start);
			while (p[len + start] && !ft_isspace(p[len + start]) && !is_spe_char(p[len + start]))
				len++;
			if (len == 0)
			{
				free(t);
				*to_set += 1;
				//				printf("syntax error token great\n");
				return (0);
			}	

		}
		t->value = malloc(sizeof(char) * (len + 1));
		t->value = ft_memmove(t->value, &p[start], len + 1);
		t->value[len] = 0;
		*to_set += len + start;
	}
	return (t);
}

t_token	*create_token(char *p, int *to_set, t_mini *m)
{
	if (p)
	{
		if (*p == '>')
		{
			if (*(p + 1) == '>')
				return (token_double_great_less(p, to_set, m));
			else
				return (token_great_less(p, to_set, m));
		}
		else if (*p == '<')
		{
			if (*(p + 1) == '<')
				return (token_double_great_less(p, to_set, m));
			else
				return (token_great_less(p, to_set, m));
		}
		else if (*p == '|')
			return (token_pipe_nl(p, to_set, m));
		else if (*p == '\n')
			return (token_pipe_nl(p, to_set, m));
		else
			return (token_word(p, to_set, m));
		//	t->value = get_tokenvalue(p, to_set);
	}
}


int create_token_list(char *s, t_list **l, t_mini *m)
{
	int		i;
	t_list	*new;
	int	len;
	t_token *t;

	i = 0;
	if (s)
	{
		len = ft_strlen(s);
		while (i < len)
		{
			if (!ft_isspace(s[i]))
			{
				//	printf("&s[i] %s\n", &s[i]);
				t = create_token(&s[i], &i, m);
				if (!t)
				{
					// syntax error
					print_error("shell", 0, errno, "syntax error lexer");
					//	ft_putnbr_fd(((t_token *)(ft_lstlast(*l)->content))->type, 2);
					//		t = ft_lstlast((*l))->content;
					//	printf("s[i] %s\n", &s[i]);
					//		printf("token type %d\n", t->type);
					//	ft_putstr_fd("syntax error, could not create token\n", 2);
ft_lstclear(l, del_token);
					return (FAILURE);
				}
				new = ft_lstnew(t);
				ft_lstadd_back(l, new);

			}
			else
				i++;
			//	printf("s[i %d] = %c, len %ld\n", i, s[i], ft_strlen(s));
		}
		new = ft_lstnew(create_token("\n", &i, m));
		ft_lstadd_back(l, new);
	}
	return (SUCCESS);
}

int	lexer(t_mini *m) // return FAILURE if could not create tokens
{
	t_list	*l;
	int ret;

	l = 0;
	//			printf("before lexer s %s\n", m->s);
	ret = create_token_list(m->s, &l, m);
	m->token_list = l;
	//		printf("after lexer\n");
	//	print_list(l, print_token);
	return (ret);
}
