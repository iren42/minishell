/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 21:04:51 by iren              #+#    #+#             */
/*   Updated: 2022/06/16 23:10:00 by isabelle         ###   ########.fr       */
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
	print_token_list(mini->token_list);
	print_cmdtab_list(mini->cmdtab_list);
}

void	print_token(t_token *t)
{
	printf("token type %d\t", t->type);
	printf("value %s\n", t->value);

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

void	print_cmdtab(t_cmdtab *c)
{
	printf("cmd =%s\n", c->cmd);
	print_list(c->arg_list, &print_arg);
	print_list(c->redir_list, &print_redir);
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

void	 print_token_list(t_list *l)
{
	printf("--LIST--\n");
	t_list	*head;
	head = l;
	while (head)
	{
		print_token(head->content);
		head = head->next;
	}
	printf("--LIST END--\n\n");
}
void	 print_cmdtab_list(t_list *l)
{
	printf("--LIST--\n");
	t_list	*head;
	head = l;
	while (head)
	{
		print_cmdtab(head->content);
		head = head->next;
	}
	printf("--LIST END--\n\n");
}

void	print_export(void  *o)
{
	t_export *e;

	e = (t_export *)o;
	printf("\te index = %d\n", e->index);
	printf("\te name = %s\n", e->name);
	printf("\te value = %s\n", e->value);
}
