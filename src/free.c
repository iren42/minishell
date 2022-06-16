/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 20:57:54 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/16 16:47:23 by isabelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split != 0)
	{
		while (split[i] != 0)
		{
			free(split[i]);
			i++;
		}
		free(split);
		split = 0;
	}
}


void	del_token(void *token)
{
	t_token	*t;

	t = (t_token *) token;
	free(t->value);
	free(token);
}
