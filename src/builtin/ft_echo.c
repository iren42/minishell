/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 22:49:22 by iren              #+#    #+#             */
/*   Updated: 2022/06/22 00:42:38 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo -nnn salut
// salut without NL

// echo
// echo $NOTEXISTING
// NL

// echo -n -n
// NOTHING

// echo salut      f
// salut f

// echo '"$USER"'
// "$USER"

// echo "'$USER'   "
// 'iren'   

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

void	print_without_first_quote(char *s)
{
	int	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	if (is_quote(s[i]))
		i++;
	while (s[i] && i < len - 1)
	{
		ft_putchar_fd(s[i], STDIN);
		i++;
	}
	if (!is_quote(s[len - 1]))
		ft_putchar_fd(s[len - 1], STDIN);

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
				//	ft_putstr_fd(opt, STDIN);
					print_without_first_quote(opt);
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
