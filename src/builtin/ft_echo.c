/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 22:49:22 by iren              #+#    #+#             */
/*   Updated: 2022/06/22 00:15:53 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo -nnn salut
// salut without NL

// echo
// NL

// echo -n -n
// NOTHING

// echo salut      f
// salut f

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

int	ft_echo(t_cmdtab *c)
{
	t_list	*l;
	char	*opt;
	int	nl;

	l = c->arg_list;
	if (l == 0)
		ft_putstr_fd("\n", STDIN);
	else
	{
		nl = 1;
		while (l)
		{
			opt = get_arg_value(l->content);
			if (opt)
			{
				if (opt[0] == '-' && is_only_filled_with_n(opt))
					nl = 0;
				else
				{
					ft_putstr_fd(opt, STDIN);
					if (l->next)
						ft_putstr_fd(" ", STDIN);
				}
			}
			l = l->next;
		}
		if (nl)
			ft_putstr_fd("\n", STDIN);
	}
	return (SUCCESS);
}
