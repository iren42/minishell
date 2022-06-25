/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <gufestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:28:08 by gufestin          #+#    #+#             */
/*   Updated: 2022/06/25 05:53:48 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(t_cmdtab *cmdtab, char **split_cmd, char **split_env)
{
	if (cmdtab->cmd == 0)
		return ;
	if (execve(cmdtab->cmd, split_cmd, split_env) == -1)
	{
		print_error("shell", split_cmd[0], 0, "command not found");
		g_errno = 127;
	}
}

void	execute_cmd(char **split_cmd, t_cmdtab *c, t_exec *e)
{
	if (c->type == EXPORT)
		ft_export(c);
	else if (c->type == UNSET)
		ft_unset(c);
	else if (c->type == CD)
		ft_cd(c);
	else if (c->type == ECHO)
		ft_echo(c);
	else if (c->type == ENV)
		ft_env(c);
	else if (c->type == PWD)
		ft_pwd();
	else if (c->type == EXIT)
		ft_exit(c);
	else
		ft_execve((t_cmdtab *)(e->cmdtabl->content), split_cmd, e->split_env);
}

void	exec_no_fork(t_exec *e, t_cmdtab *ptr)
{
	char	**split_cmd;

	split_cmd = ft_split_cmd(e->m, 0);
	execute_cmd(split_cmd, ptr, e);
	free_split(split_cmd);
}

static pid_t	*init_var_pids(int nb_cmd)
{
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * nb_cmd);
	if (!pids)
		exit(1);
	return (pids);
}

int	executor(t_mini *mini)
{
	t_executor_variables	var;
	t_cmdtab				*ptr;

	if ((t_list *)(mini->cmdtab_list) == NULL)
		return (0);
	ptr = get_cmdtab_ptr(mini->cmdtab_list->content);
	init_t_exec(&(var.e), mini);
	if (var.e.nb_cmd == 1 && (ptr->type == CD || ptr->type == UNSET
			|| ptr->type == EXPORT || ptr->type == EXIT))
		exec_no_fork(&(var.e), ptr);
	else
	{
		var.pids = init_var_pids(var.e.nb_cmd);
		var.ends = init_pipes(var.e.nb_cmd);
		open_pipes(var.ends, var.e.nb_cmd);
		exec_cmdtab_list(&(var.e), var.pids, var.ends);
		close_all_pipes(var.ends, var.e.nb_cmd);
		var.err = ft_wait(var.pids, var.e.nb_cmd);
		free_pipes(var.ends, var.e.nb_cmd);
		free(var.pids);
		signal_handler();
	}
	free_split(var.e.split_env);
	return (var.err);
}
