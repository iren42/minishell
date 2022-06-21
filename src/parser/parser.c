/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:05:28 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/21 16:30:12 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmdtab(t_cmdtab *c, t_mini *m)
{
	c->cmd = 0;
	c->arg_list = 0;
	c->redir_list = 0;
	c->m = m;
}


int	is_cmd(t_token *t)
{
	char	*buff;
	int	is_cmd;

	buff = 0;
	is_cmd = access(t->value, X_OK);
	if (is_cmd == -1)
		buff = get_cmd(t->m->env_list, t->value);
	//	printf("buff %s\n",  buff);
	if (buff == 0 && is_cmd == -1)
		return (0);
	free(buff);
	return (1);

}
int	fill_cmd(t_token *t, t_cmdtab *ct, int *ret)
{
	int	a;


	a = is_cmd(t);
	if (a == 1 && t->type == WORD && !ct->cmd)
	{
		if (access(t->value, X_OK) == 0)
		{
			ct->cmd = ft_strdup(t->value);
			(*ret)++;
		}
		else
		{
			ct->cmd = get_cmd(t->m->env_list, t->value);
			if (ct->cmd)
				(*ret)++;
		}
	}
	return (0);
}

int	fill_args(t_token *t, t_cmdtab *c, int *ret)
{
	t_arg	*new;

	if (t->type == WORD && *ret == 0)
	{
		//		printf("is cmd %d, %s\n", is_cmd(t), t->value);
		new = malloc(sizeof(t_arg));
		if (!new)
			exit(1);

		new->value = ft_strdup(t->value);
		ft_lstadd_back(&c->arg_list, ft_lstnew(new));
		return (1);
	}
	return (0);
}

int	fill_redir(t_token *t, t_cmdtab *c, int *ret)
{
	t_redir	*new;

	if (t->type == GREAT || t->type == DOUBLE_GREAT || t->type == LESS)
	{	new = malloc(sizeof(t_redir));
		if (!new)
			exit(1);
		if (t->type == GREAT)
			new->type = RE_GREAT;
		else if (t->type == DOUBLE_GREAT)
			new->type = RE_DOUBLE_GREAT;
		else if (t->type == LESS)
			new->type = RE_LESS;
		else
			;
		new->filename = ft_strdup(t->value);
		if (!new->filename)
			exit(1);
		ft_lstadd_back(&c->redir_list, ft_lstnew(new));
	}
}
t_list	*parser(t_mini *m)
{
//	printf("\n--IN PARSER--\n");
	t_list	*cmd_list;
	t_cmdtab	*new;
	t_list	*l;
	int	ret;

	l = m->token_list;
	cmd_list = 0;
	new = malloc(sizeof(t_cmdtab));
	if (!new)
		exit(1);
	init_cmdtab(new, m);
	if (l)
	{
	while (get_token_type(l->content) != NL)
	{
		ret = 0;
		//	print_token(l->content);
		fill_cmd(l->content, new, &ret);
		fill_args(l->content, new, &ret);
		fill_redir(l->content, new, &ret);
		//	printf("cmd? %s\n",new->cmd);
		if (get_token_type(l->content) == PIPE || get_token_type(l->content) == SEMI)
		{
	//		printf("add in list\n");
			ft_lstadd_back(&cmd_list, ft_lstnew(new));
			new = malloc(sizeof(t_cmdtab));
			if (!new)
				exit(1);
			init_cmdtab(new, m);
			//	ret = 0;
		}
		l = l->next;
	}
	ft_lstadd_back(&cmd_list, ft_lstnew(new));
//	printf("--OUT PARSER--\n");
	//	print_list(cmd_list, );
//	ft_lstclear(m->token_list, &del_token);
	}
	return (cmd_list);

}
