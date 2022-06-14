/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 21:04:51 by iren              #+#    #+#             */
/*   Updated: 2022/06/14 14:36:18 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_split(char **s)
{
	int	i;

	if (s)
	{
		i = 0;
		printf("\n\n--SPLIT--\n");
		while (s[i] != 0)
		{
			printf("s[%d] = %s\n", i, s[i]);
			i++;
		}
		printf("--SPLIT END--\n");
	}
}

void	print_tmini(t_mini *mini)
{
	int	i;

	i = 0;
//	printf("s = %s\n", mini->s);
	print_lst(mini->tokens);
}

void	print_token(t_token *t)
{
	printf("token type %d\t", t->type);
	printf("value %s\n", t->value);

}

void	 print_lst(t_list *head)
{
	printf("--LIST--\n");
	while (head)
	{
	print_token(head->content);
		head = head->next;
	}
	printf("--LIST END--\n");
}
