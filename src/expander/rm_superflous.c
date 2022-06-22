/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_superflous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:24:36 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/22 09:14:47 by iren             ###   ########.fr       */
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

	new = malloc(sizeof(*new));
	new->c = c;
	new->index = i;
	ft_lstadd_front(l, ft_lstnew(new));
}

void pop(t_list **l, char *s, int *index_close)
{
	t_list	*tmp;
	int	index_open;
	int	i;
	int	metacharacter;

	i = 0;
	metacharacter = 0;
	tmp = *l;
	index_open = get_quote_index(tmp->content);
	*l = (*l)->next;
	ft_lstdelone(tmp, &del_quote);
	while (s[index_open + i] && index_open + i < *index_close)
	{
		if (ft_strchr("$ |<>\t\n\v\f\r", s[index_open + i]) != 0)
		{
			metacharacter++;
			break ;
		}
		i++;
	}
	if (!metacharacter)
	{
		ft_memmove(&s[*index_close], &s[*index_close + 1], ft_strlen(s));
		ft_memmove(&s[index_open], &s[index_open + 1], ft_strlen(s));
		//	printf("2nd memmove %s\n", s);
		*index_close -= 2;
	}
}

char	*rm_superflous(char *s) // verify quotes closed and rm useless quotes
{
	int	i;
	t_list	*quote_list;

	i = 0;
	quote_list = 0;
	if (s)
	{
	while (s[i])
	{
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
	}
	//	printf("LIST\n");
	//	print_list(quote_list, &print_char);
	//	printf("LIST\n");
	ft_lstclear(&quote_list, &del_quote);
//	printf("rm_superflous() final s %s\n", s);
	}
	return (s);
}
