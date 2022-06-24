/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 22:49:22 by iren              #+#    #+#             */
/*   Updated: 2022/06/24 23:34:57 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_only_filled_with_n(char *s)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	if (i == 1)
		return (0);
	return (1);
}

static void	get_index_first_nd_last_quote(char *s, int *f, int *l)
{
	int		i;
	int		len;
	char	q;

	i = 0;
	len = ft_strlen(s) - 1;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			q = s[i];
			*f = i;
			break ;
		}
		i++;
	}
	while (len >= 0)
	{
		if (s[len] == '"' || s[len] == '\'')
		{
			*l = len;
			break ;
		}
		len--;
	}
}

static void	print_without_first_closing_quotes(char *s)
{
	int		i;
	size_t	len;
	int		first;
	int		last;

	i = 0;
	len = ft_strlen(s);
	first = -1;
	last = -1;
	get_index_first_nd_last_quote(s, &first, &last);
	while (i < len && s[i])
	{
		if (i == first || i == last)
			;
		else
			ft_putchar_fd(s[i], 1);
		i++;
	}
}

static void	in_loop(char *opt, t_list *l, int *nl)
{
	if (opt[0] == '-' && is_only_filled_with_n(opt))
		*nl = 0;
	else
	{
		print_without_first_closing_quotes(opt);
		if (l->next)
			ft_putstr_fd(" ", 1);
	}
}

int	ft_echo(t_cmdtab *c)
{
	t_list	*l;
	char	*opt;
	int		nl;

	l = c->arg_list;
	if (l == 0)
		ft_putstr_fd("\n", 1);
	else
	{
		nl = 1;
		while (l)
		{
			opt = get_arg_value(l->content);
			if (opt)
				in_loop(opt, l, &nl);
			l = l->next;
		}
		if (nl)
			ft_putstr_fd("\n", 1);
	}
	return (SUCCESS);
}
