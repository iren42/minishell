/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:31:53 by iren              #+#    #+#             */
/*   Updated: 2022/06/20 15:14:00 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_list	*cmdtab_list)
{
	char	*pwd;
	
	pwd = getenv("PWD");
	if (pwd)
	{
		printf("%s\n", pwd);
		return (SUCCESS);
	}
	return (FAILURE);
}
