/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 00:06:55 by gufestin          #+#    #+#             */
/*   Updated: 2022/06/25 02:28:23 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_ends(int i, t_exec *e, int **ends)
{
	if (i != e->nb_cmd - 1)
	{
		dup2(ends[i][1], STDOUT);
		close(ends[i][1]);
		close(ends[i][0]);
	}
	if (i > 0)
	{
		dup2(ends[i - 1][0], STDIN);
		close(ends[i - 1][0]);
		close(ends[i - 1][1]);
	}
}

static void	delete_heredoc_files(t_exec *e)
{
	t_list	*tmp;
	char	*eof;

	tmp = ((t_cmdtab *)(e->cmdtabl->content))->redir_list;
	while (tmp)
	{
		eof = ft_strjoin(((t_redir *)(tmp->content))->filename, ".heredoc");
		if (!eof)
			exit(1);
		unlink(eof);
		free(eof);
		tmp = tmp->next;
	}
}

void	exec_child(t_exec *e, int **ends, char **split_cmd, int i)
{
	int		fd_in;
	int		fd_out;

	close_ends(i, e, ends);
	fd_in = ex_infile(e, STDIN);
	if (fd_in != STDIN)
	{
		dup2(fd_in, STDIN);
		close(fd_in);
	}
	delete_heredoc_files(e);
	fd_out = ex_outfile(e, STDOUT);
	if (fd_out != STDOUT)
	{
		dup2(fd_out, STDOUT);
		close(fd_out);
	}
	close_all_pipes_but_index(ends, e->nb_cmd, i);
	execute_cmd(split_cmd, e->cmdtabl->content, e);
	exit(g_errno);
}
