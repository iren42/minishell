/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:05:28 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/18 14:32:08 by isabelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmdtab(t_cmdtab *c)
{
	c->cmd = 0;
	c->arg_list = 0;
	c->redir_list = 0;
}

int	get_token_type(t_token *t)
{
	if (t)
		return (t->type);
	return (0);
}
char	*get_token_value(t_token *t)
{
	if (t)
		return (t->value);
	return (0);
}

int	is_cmd(t_token *t)
{
	char	*buff;
	int	is_cmd;

	buff = 0;
	is_cmd = access(t->value, X_OK);
	if (is_cmd == -1)
		buff = get_cmd(t->m->env, t->value);
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
			ct->cmd = get_cmd(t->m->env, t->value);
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

void	del_redir(void *o)
{
	t_redir *r;

	r = (t_redir *)o;
	free(r->filename);
	free(r);
}

void	del_arg(void *o)
{
	t_arg *a;

	a = (t_arg *)o;
	free(a->value);
	free(a);
}

void	del_cmdtab(void *o)
{
	t_cmdtab	*c;

	c = (t_cmdtab *)o;
	free(c->cmd);
	ft_lstclear(&c->arg_list, del_arg);
	ft_lstclear(&c->redir_list, del_redir);
	free(c);
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
	init_cmdtab(new);
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
			init_cmdtab(new);
			//	ret = 0;
		}
		l = l->next;
	}
	ft_lstadd_back(&cmd_list, ft_lstnew(new));
//	printf("--OUT PARSER--\n");
	//	print_list(cmd_list, );
//	ft_lstclear(m->token_list, &del_token);
	return (cmd_list);

}
