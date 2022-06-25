/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:31:53 by iren              #+#    #+#             */
/*   Updated: 2022/06/25 02:32:02 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*pwd;
	char	buf[BUF_SIZE];

	pwd = getcwd(buf, BUF_SIZE);
	if (pwd)
	{
		ft_putstr_fd(pwd, STDIN);
		ft_putstr_fd("\n", STDIN);
		return (SUCCESS);
	}
	print_error("shell: pwd", NULL, 0, "BUF_SIZE too small");
	return (FAILURE);
}
