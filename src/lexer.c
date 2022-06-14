/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:42:06 by iren              #+#    #+#             */
/*   Updated: 2022/06/14 09:46:20 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(int c)
{
	if (c == '"' || c == '\'')
		return (c);
	return (0);
}

char	*has_red(const char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] == '<' || s[i] == '>')
				return ((char *)&s[i]);
			i++;
		}
	}
	return (0);
}
/*
   int	ft_nb_words(const char *s, const char *c)
   {
   int	i;
   int	nb_w;
   int	q;

   i = 0;
   nb_w = 0;
   if (s != 0 && c)
   {
   while (s[i])
   {
   while (ft_strchr(c, s[i]) && s[i])
   {
   i++;
   }
   if (s[i] && !ft_strchr(c, s[i]) )
   {
   nb_w++;
   if (!is_quote(s[i]))
   {
   while (s[i] && !ft_strchr(c, s[i]) && !is_quote(s[i]))
   {
   i++;
   }
   }
   else
   {
   q = s[i++];
   while (s[i] && s[i] != q)
   {
   i++;
   }
   i++;

   }
   }
   }
   }
   printf("nb word = %d\n", nb_w);
   return (nb_w);
   }

   int	ft_calc_nb_split1(char **split)
   {
   int	i;

   i = 0;
   while (split[i] != 0)
   {

   i++;
   }
   printf("nb split1 %d\n", i);
   return (i);
   }

   int	ft_calc_nb_split2(char ***split)
   {
   int res;
   int	i;
   int	j;

   res = 0;
   i = 0;
   j = 0;
   while (split[i] != 0)
   {
   j = 0;
   while (split[i][j] != 0)
{
	res++;
	j++;
}
i++;
}
printf("nb split2 %d\n", res);
return (res);
}

char	**split_tosplit(char ***split)
{
	char	**res;
	int	nb_split;
	int	i;
	int	j;
	int	a;

	i = 0;
	j = 0;
	a = 0;
	nb_split = ft_calc_nb_split2(split);
	res = malloc(sizeof(char*) * (nb_split + 1));
	while (split[i] != 0)
	{
		j = 0;
		while (split[i][j] != 0)
		{
			res[a++] = split[i][j++];
		}
		i++;

	}
	res[a] = 0;
	return (res);
}*/
int	is_spe(int c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

char	*get_tokenvalue(char *s)
{
	int		i;
	char	*value;

	i = 0;
	value = 0;
	while (s[i] && !is_spe(s[i]))
	{
		i++;
	}
	value = malloc(sizeof(char) * (i + 1));
	printf("len %d, s %s\n", i, s);
	value = ft_memmove(value, s, i + 1);
	printf("value %s\n", value);
	return (value);
}

void *create_token(char *s)
{
	int		i;
	t_token	*t;
	char	*p;

	i = 0;
	t = malloc(sizeof(t_token));
	if (!t)
		exit(1);
	while (s[i])
	{
		
	if (p = ft_strnstr(s, ">", ft_strlen(s)))
	{
		printf("pointeur %s\n", p);
		if (ft_strnstr(p + 1, ">", ft_strlen(p + 1)))
		{
			t->type = DOUBLE_GREAT;
			p++;
		}
		else
			t->type = GREAT;
		t->value = get_tokenvalue(p + 1);

	}
	else if ()
	else
	{
		t->type = NONE;
		t->value = ft_strdup("NONE\n");
	}
	i++;
	}
	return ((void *)t);
}

t_list	*lexer(t_mini *m)
{
	t_list	*t;
	t_list	*new;
	char	**split_pipe;
	int	i;
	int	a;

	i = 0;
	t = 0;
	split_pipe = ft_splitsh(m->s, "|");
	if (!split_pipe)
		exit(1);
	while (split_pipe[i] != 0)
	{
		new = ft_lstnew(create_token(split_pipe[i]));
		if (new)
			ft_lstadd_back(&t, new);
		else
			exit(1);
		i++;

	}
	print_lst(t);
}
