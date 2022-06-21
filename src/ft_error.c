/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 22:52:57 by iren              #+#    #+#             */
/*   Updated: 2022/06/21 15:08:12 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *msg, int code)
{
	ft_putstr_fd(msg, 1);
	exit(code);
}

void	print_error(char *where, char *file, int err, char *msg)
{
	if (!msg)
		ft_putstr_fd("minishell: ", STDERR);
	if (where)
	{
		ft_putstr_fd(where, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	if (file)
	{
		ft_putstr_fd(file, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	if (msg)
		ft_putstr_fd(msg, STDERR);
	else
		ft_putstr_fd(strerror(err), STDERR);
	ft_putstr_fd("\n", STDERR);
}
