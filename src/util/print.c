/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 21:04:51 by iren              #+#    #+#             */
/*   Updated: 2022/06/25 00:59:16 by gufestin         ###   ########.fr       */
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

void	print_list(t_list *l, void (*f)(void *))
{
	t_list	*head;

	head = l;
	while (head)
	{
		f(head->content);
		head = head->next;
	}
}

void	print_tmini(t_mini *mini)
{
	int	i;

	i = 0;
	printf(BLU "----TOKEN LIST START----\n");
	print_list(mini->token_list, &print_token);
	printf("----TOKEN LIST END----\n");
	printf(PUR "----CMD TABLE LIST START----\n");
	print_list(mini->cmdtab_list, &print_cmdtab);
	printf("----CMD TABLE LIST END----\n" RESET);
}

void	print_token(void *o)
{
	t_token	*t;

	t = (t_token *)o;
	printf("token type %d.\t", t->type);
	printf("value %s.\n", t->value);
}

void	print_arg(void *o)
{
	t_arg	*a;

	a = (t_arg *)o;
	printf("\targ value = %s\n", a->value);
}
