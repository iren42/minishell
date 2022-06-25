/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 04:37:01 by iren              #+#    #+#             */
/*   Updated: 2022/06/25 05:58:09 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmdtab_list(t_exec *e, pid_t *pids, int **ends)
{
	int		i;
	char	**split_cmd;

	i = 0;
	signal_handler_child();
	while (i < e->nb_cmd)
	{
		split_cmd = ft_split_cmd(e->m, i);
		pids[i] = fork();
		if (pids[i] == -1)
			exit(1);
		if (pids[i] == 0)
		{
			exec_child(e, ends, split_cmd, i);
		}
		e->cmdtabl = e->cmdtabl->next;
		free_split(split_cmd);
		i++;
	}
}
/*
void	executor_pipes(t_executor_variables *var)
{
	var->ends = init_pipes((var->e).nb_cmd);
	open_pipes(var->ends, (var->e).nb_cmd);
	exec_cmdtab_list(&(var->e), var->pids, var->ends);
	close_all_pipes(var->ends, (var->e).nb_cmd);
	var->err = ft_wait(var->pids, (var->e).nb_cmd);
	free_pipes(var->ends, (var->e).nb_cmd);
	free(var->pids);
	signal_handler();
}
*/
