/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_superflous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:24:36 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/24 12:32:49 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		matching(char b1, char b2)
{
	if (b1 == '"' && b2 == '"')
		return (1);
	if (b1 == '\'' && b2 == '\'')
		return (1);
	return (0);
}

void	push(t_list **l, char c, char *s, int i)
{
	t_quote	*new;
	t_list	*a;

	ft_putstr_fd("push\n", 2);
	new = malloc(sizeof(*new));
	new->c = c;
	new->index = i;
	a = ft_lstnew(new);
	ft_lstadd_front(l, a);
}

void pop(t_list **l, char *s, int *index_close)
{
	t_list	*tmp;
	int	index_open;
	int	i;
	int	metacharacter;

	i = 0;
	ft_putstr_fd("pop\n", 2);
	metacharacter = 0;
	tmp = *l;

	*l = (*l)->next;
	ft_lstdelone(tmp, &del_quote);
}

int	are_quotes_closed(char *s) // verify quotes closed
{
	int	i;
	t_list	*quote_list;

	i = 0;
	quote_list = 0;
	if (s)
	{
		while (s[i])
		{
		//	printf("s[i] = %c\n", s[i]);
			if (is_quote(s[i]))
			{
				if (quote_list)
				{
					if (matching(get_quote_char(quote_list->content), s[i]))
						pop(&quote_list, s, &i);
					else
						push(&quote_list, s[i], &s[i], i);
				}
				else
					push(&quote_list, s[i], &s[i], i);
			}
			i++;
		}
		if (quote_list != 0)
		{
			printf("error syntax quotes\n");
			ft_lstclear(&quote_list, &del_quote);
			return (0);
		}
		//	printf("LIST\n");
		//	print_list(quote_list, &print_quote);
		//	printf("LIST\n");
		//		printf("check closed quotes() final s %s\n", s);
	}
	return (1);
}

char	*rm_superflous(char *s) // rm superflous quotes
{
	int	i;
	int	start;
	int	meta;
	t_list	*quote_list;

	i = 0;
	quote_list = 0;
	meta = 0;
	printf("in rm superflous\n");
	if (s)
	{
		while (s[i])
		{
			if (s[i] == '\'')
			{
				i++;
				while (s[i] && s[i] != '\'')
					i++;
			}
			else if (s[i] == '"')
			{
				start = i++;
				while (s[i] && s[i] != '"')
				{
					if (ft_strchr(" <>$|\n\'",s[i]))
						meta = 1;
					i++;
				}
				if (meta == 0)
				{
				ft_memmove(&s[i], &s[i + 1], ft_strlen(s) + 1);
					printf("1st mem %s, %s\n", s, &s[i]);
				ft_memmove(&s[start], &s[start + 1], ft_strlen(s) + 1);
					printf("2 mem %s, %s\n", s, &s[start]);
				i -= 2;
				}

			}
			i++;
		}
	}
	printf("end rm superflous\n");
	return (s);
}
