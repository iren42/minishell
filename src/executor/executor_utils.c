/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 00:03:05 by gufestin          #+#    #+#             */
/*   Updated: 2022/06/25 00:28:43 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wait(pid_t *pids, int n)
{
	int	status;
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
	{
		err = WEXITSTATUS(status);
		g_errno = err;
	}
	return (err);
}

int	redir_error(t_redir *redir, t_exec *e)
{
	struct stat	buf;

	if (stat(redir->filename, &buf) == 0)
	{
		if (buf.st_mode & S_IFDIR)
		{
			print_error("shell", redir->filename, 0, "Is a directory");
			return (1);
		}
		else if ((buf.st_mode & S_IXUSR) == 0)
		{
			print_error("shell", redir->filename, 0, "Permission denied");
			return (1);
		}
	}
	print_error("shell", redir->filename, 0, "No such file or directory");
	return (1);
}

char	*is_builtin(char *cmd, t_mini *m)
{
	int	i;

	i = 0;
	if (m->split_builtin)
	{
		while (m->split_builtin[i])
		{
			if (ft_memcmp(cmd, m->split_builtin[i], ft_strlen(cmd) + 1) == 0)
				return (m->split_builtin[i]);
			i++;
		}
	}
	return (0);
}

void	*init_t_exec(t_exec *e, t_mini *m)
{
	e->split_env = ft_split_env(m);
	e->nb_cmd = ft_lstsize(m->cmdtab_list);
	e->cmdtabl = m->cmdtab_list;
	e->m = m;
	if (!e->split_env || !e->cmdtabl)
		exit(1);
}
