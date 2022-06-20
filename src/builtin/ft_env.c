/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:24:27 by iren              #+#    #+#             */
/*   Updated: 2022/06/20 16:00:05 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	ft_env(t_list *cmdtab_list)
int	ft_env(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->env[i])
	{
		printf("%s\n", mini->env[i]);
		i++;
	}
	// print list texport
	return (SUCCESS);
}
