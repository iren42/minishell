/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 22:06:40 by iren              #+#    #+#             */
/*   Updated: 2022/06/25 02:02:27 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd_type	get_cmd_type(char *type)
{
	if (ft_memcmp(type, "export", ft_strlen(type) + 1) == 0)
		return (EXPORT);
	else if (ft_memcmp(type, "pwd", ft_strlen(type) + 1) == 0)
		return (PWD);
	else if (ft_memcmp(type, "echo", ft_strlen(type) + 1) == 0)
		return (ECHO);
	else if (ft_memcmp(type, "cd", ft_strlen(type) + 1) == 0)
		return (CD);
	else if (ft_memcmp(type, "unset", ft_strlen(type) + 1) == 0)
		return (UNSET);
	else if (ft_memcmp(type, "env", ft_strlen(type) + 1) == 0)
		return (ENV);
	else if (ft_memcmp(type, "exit", ft_strlen(type) + 1) == 0)
		return (EXIT);
	return (OTHER);
}

void	fill_cmd(t_token *t, t_cmdtab *ct, int *ret)
{
	if (t->type == WORD && t->type == WORD && !ct->cmd)
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
			else
			{
				ct->cmd = ft_strdup(t->value);
				(*ret)++;
			}
		}
		ct->type = get_cmd_type(t->value);
	}
}

void	fill_args(t_token *t, t_cmdtab *c, int *ret)
{
	t_arg	*new;

	if (t->type == WORD && *ret == 0)
	{
		new = malloc(sizeof(t_arg));
		if (!new)
			exit(1);
		new->value = ft_strdup(t->value);
		ft_lstadd_back(&c->arg_list, ft_lstnew(new));
	}
}

void	fill_redir(t_token *t, t_cmdtab *c)
{
	t_redir	*new;

	if (t->type == GREAT || t->type == DOUBLE_GREAT || t->type == LESS
		|| t->type == DOUBLE_LESS)
	{
		new = malloc(sizeof(t_redir));
		if (!new)
			exit(1);
		if (t->type == GREAT)
			new->type = RE_GREAT;
		else if (t->type == DOUBLE_GREAT)
			new->type = RE_DOUBLE_GREAT;
		else if (t->type == LESS)
			new->type = RE_LESS;
		else if (t->type == DOUBLE_LESS)
			new->type = RE_DOUBLE_LESS;
		new->filename = ft_strdup(t->value);
		if (!new->filename)
			exit(1);
		ft_lstadd_back(&c->redir_list, ft_lstnew(new));
	}
}
