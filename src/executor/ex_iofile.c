/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_iofile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:53:04 by gufestin          #+#    #+#             */
/*   Updated: 2022/06/24 23:53:39 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ex_infile(t_exec *e, int fd_in, int child, int **fd)
{
	t_list	*tmp;

	tmp = ((t_cmdtab *)(e->cmdtabl->content))->redir_list;
	while (tmp)
	{
		if (fd_in != STDIN)
			close(fd_in);
		if (get_redir_type(tmp->content) == RE_LESS)
			fd_in = open(((t_redir *)(tmp->content))->filename, O_RDONLY);
		else if (get_redir_type(tmp->content) == RE_DOUBLE_LESS)
			fd_in = ft_heredoc(((t_redir *)(tmp->content))->filename);
		if (fd_in < 0)
		{
			redir_error(tmp->content, e);
			exit(1);
		}
		tmp = tmp->next;
	}
	return (fd_in);
}

int	ex_outfile(t_exec *e, int fd_out, int child, int **fd)
{
	t_list	*tp;

	tp = ((t_cmdtab *)(e->cmdtabl->content))->redir_list;
	while (tp)
	{
		if (fd_out != STDOUT)
			close(fd_out);
		if (get_redir_type(tp->content) == RE_GREAT)
			fd_out = open(((t_redir *)(tp->content))->filename,
					O_CREAT | O_RDWR | O_TRUNC, 0664);
		else if (get_redir_type(tp->content) == RE_DOUBLE_GREAT)
			fd_out = open(((t_redir *)(tp->content))->filename,
					O_CREAT | O_RDWR | O_APPEND, 0664);
		if (fd_out < 0)
		{
			redir_error(tp->content, e);
			exit(1);
		}
		tp = tp->next;
	}
	return (fd_out);
}
