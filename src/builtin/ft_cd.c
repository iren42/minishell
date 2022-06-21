/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:37:30 by iren              #+#    #+#             */
/*   Updated: 2022/06/21 20:33:24 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdtab	*create_cmdtab(char *cmd, t_list *argl, t_mini *m)
{
	t_cmdtab	*c;

	c = malloc(sizeof(t_cmdtab));
	if (!c)
		exit(1);
	c->cmd = ft_strdup(cmd);
	c->arg_list = argl;
	c->redir_list = 0;
	c->m = m;
	return (c);
}

t_arg	*create_arg(char *value)
{
	t_arg	*new;

	new = malloc(sizeof(t_arg));
	if (!new)
		exit(1);
	new->value = value;
	return (new);
}

t_list	*create_arg_list(char *pwd, char *oldpwd)
{
	t_arg	*b;
	t_arg	*a;
	t_list	*argl;

	argl = 0;
	a = create_arg(oldpwd);
	b = create_arg(pwd);
	ft_lstadd_back(&argl, ft_lstnew(a));
	ft_lstadd_back(&argl, ft_lstnew(b));
	return (argl);
}

void	update_oldpwd_nd_pwd(t_cmdtab *c)
{
	t_cmdtab	*new_c;
	char	buf[BUF_SIZE];
	char	*oldpwd;
	char	*pwd;
	t_list	*argl;

	oldpwd = ft_strjoin("OLDPWD=", ft_getenv("PWD", c->m->env_list));
	pwd = ft_strjoin("PWD=", getcwd(buf, BUF_SIZE));
	if (!oldpwd || !pwd)
		exit(1);	
	argl = create_arg_list(pwd, oldpwd);
	if (!argl)
		exit(1);

	new_c = create_cmdtab("export", argl, c->m);
	if (!new_c)
		exit(1);

	ft_export(new_c);
	//	print_cmdtab(new_c);
	del_cmdtab(new_c);
}

int	ft_cd(t_cmdtab *c)
{
	char	*path;

	if (c->arg_list == 0)
		path = ft_getenv("HOME", c->m->env_list);
	else if (ft_lstsize(c->arg_list) > 2)
	{
		print_error("shell: cd", NULL, 0, "Too many arguments");
		return (FAILURE);
	}
	else
		path = get_arg_value(c->arg_list->content);
	if (ft_memcmp(path, "~", 2) == 0)
		path = ft_getenv("HOME", c->m->env_list);
	//	printf("path %s\n", path);
	if (chdir(path))
	{
		print_error("shell: cd", path, errno, "No such file or directory");
		return (FAILURE);
	}
	update_oldpwd_nd_pwd(c);
	return (SUCCESS);
}
