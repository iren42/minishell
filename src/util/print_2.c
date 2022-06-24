/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 00:57:03 by gufestin          #+#    #+#             */
/*   Updated: 2022/06/25 00:58:03 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redir(void *o)
{
	t_redir	*a;

	a = (t_redir *)o;
	printf("\tredir filename = %s\n", a->filename);
	printf("\tredir type = %d\n", a->type);
}

void	print_cmdtab(void *o)
{
	t_cmdtab	*c;

	c = (t_cmdtab *)o;
	printf("cmd =%s\n", c->cmd);
	printf("type = %d\n", c->type);
	print_list(c->arg_list, &print_arg);
	print_list(c->redir_list, &print_redir);
}

void	print_env(void *o)
{
	t_env	*e;

	e = (t_env *)o;
	printf("\te name = %s\n", e->name);
	printf("\te value = %s\n\n", e->value);
}

void	print_quote(void *o)
{
	t_quote	*a;

	a = (t_quote *)o;
	printf("quote c %c\n", a->c);
	printf("quote index %d\n", a->index);
}
