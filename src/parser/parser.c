/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:05:28 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/25 02:03:44 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_cmdtab(t_cmdtab *c, t_mini *m)
{
	c->cmd = 0;
	c->arg_list = 0;
	c->redir_list = 0;
	c->m = m;
	c->type = OTHER;
}

static void	fill_everything(t_list *l, t_cmdtab **new, t_mini *m, t_list **cmdl)
{
	int	ret;

	ret = 0;
	if (get_token_type(l->content) == NL)
		return ;
	fill_cmd(l->content, *new, &ret);
	fill_args(l->content, *new, &ret);
	fill_redir(l->content, *new);
	if (get_token_type(l->content) == PIPE)
	{
		ft_lstadd_back(cmdl, ft_lstnew(*new));
		*new = malloc(sizeof(t_cmdtab));
		if (!*new)
			exit(1);
		init_cmdtab(*new, m);
	}
}

t_list	*parser(t_mini *m)
{
	t_list		*cmd_list;
	t_cmdtab	*new;
	t_list		*l;

	if (m->token_list == 0)
		return (0);
	l = m->token_list;
	cmd_list = 0;
	new = malloc(sizeof(t_cmdtab));
	if (!new)
		exit(1);
	init_cmdtab(new, m);
	if (l)
	{
		while (l)
		{
			fill_everything(l, &new, m, &cmd_list);
			l = l->next;
		}
		if (new)
			ft_lstadd_back(&cmd_list, ft_lstnew(new));
	}
	return (cmd_list);
}
