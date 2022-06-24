/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:44:56 by gufestin          #+#    #+#             */
/*   Updated: 2022/06/24 23:45:44 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_pipes(int **ends, int n)
{
	int	i;

	i = 0;
	while (i < n - 1)
	{
		close(ends[i][0]);
		close(ends[i][1]);
		i++;
	}
}

void	close_all_pipes_but_index(int **ends, int n, int index)
{
	int	i;

	i = 0;
	while (i < n - 1)
	{
		if (i != index && (i == 0 || i != index - 1))
		{
			if (ends[i][0])
				close(ends[i][0]);
			if (ends[i][1])
				close(ends[i][1]);
		}
		i++;
	}
}
