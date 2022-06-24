/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 21:04:51 by iren              #+#    #+#             */
/*   Updated: 2022/06/24 02:24:47 by iren             ###   ########.fr       */
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

void	 print_list(t_list *l, void (*f)(void *))
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
	//	printf("s = %s\n", mini->s);
	printf(BLU "----TOKEN LIST START----\n");
	print_list(mini->token_list, &print_token);
	printf( "----TOKEN LIST END----\n" );
	printf(PUR "----CMD TABLE LIST START----\n" );
	print_list(mini->cmdtab_list, &print_cmdtab);
	printf( "----CMD TABLE LIST END----\n" RESET);
}

void	print_token(void *o)
{
	t_token *t;

	t = (t_token *)o;
	printf("token type %d.\t", t->type);
	printf("value %s.\n", t->value);

}

void	print_arg(void *o)
{
	t_arg	*a;

	a = (t_arg *)o;
	printf("\targ value = %s\n", a->value);
	//	printf("arg quote = %d\n", a->is_in_quotes);
}

void	print_redir(void *o)
{
	t_redir	*a;

	a = (t_redir *)o;
	printf("\tredir filename = %s\n", a->filename);
	printf("\tredir type = %d\n", a->type);
	//	printf("arg quote = %d\n", a->is_in_quotes);
}

void	print_cmdtab(void *o)
{
	t_cmdtab *c;

	c = (t_cmdtab *)o;
	printf("cmd =%s\n", c->cmd);
	printf("type = %d\n", c->type);
	print_list(c->arg_list, &print_arg);
	print_list(c->redir_list, &print_redir);
}

void	print_env(void  *o)
{
	t_env *e;

	e = (t_env *)o;
	//	printf("\te index = %d\n", e->index);
	printf("\te name = %s\n", e->name);
	printf("\te value = %s\n\n", e->value);
}
