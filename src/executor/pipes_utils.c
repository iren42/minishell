/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 23:50:32 by iren              #+#    #+#             */
/*   Updated: 2022/06/24 23:46:28 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_loop(int **fd, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(fd[j]);
		j++;
	}
}

int	**init_pipes(int n)
{
	int	i;
	int	**fd;

	i = 0;
	fd = 0;
	if (n > 1)
	{
		fd = (int **)malloc(sizeof(int *) * (n - 1));
		if (!fd)
			exit(1);
		while (i < (n - 1))
		{
			fd[i] = (int *)malloc(sizeof(int) * 2);
			if (!fd[i])
			{
				free_loop(fd, i);
				exit(1);
			}
			i++;
		}
	}
	return (fd);
}

void	open_pipes(int **fd, int n)
{
	int	i;

	i = 0;
	while (i < (n - 1))
	{
		if (pipe(fd[i]) < 0)
			exit(1);
		i++;
	}
}

void	free_pipes(int **ends, int n)
{
	int	i;

	i = 0;
	while (i < n - 1)
	{
		free(ends[i]);
		i++;
	}
	free(ends);
}
