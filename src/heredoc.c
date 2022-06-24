/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <gufestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 23:56:04 by gufestin          #+#    #+#             */
/*   Updated: 2022/06/24 14:46:52 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(char *eof)
{
	int	fd;
	char	*filename;
	char	*read;
	int	eof_len;

	filename = ft_strjoin(eof, ".heredoc");
	if (!filename)
		exit(1); // malloc error
	fd = open(filename, O_CREAT | O_WRONLY, 0777);
	if (fd == -1)
		exit(1); // open error
	eof_len = ft_strlen(eof) + 1;
	read = readline("> ");
	if (read)
	{
		while (ft_strncmp(read, eof, eof_len))
		{
			ft_putstr_fd(read, fd);
			ft_putstr_fd("\n", fd);
			free(read);
			read = readline("> ");
			if (!read)
			{
				ft_putstr_fd("Warning: here-document delimited by end of file\n", 2);
				// g_errno = 0;
				break ;
			}
		}
	}
	else
		ft_putstr_fd("Warning: here-document delimited by end of file\n", 2);
	// g_errno = 0;
	free(read);
	close(fd);
	fd = open(filename, O_RDONLY);
	free(filename);
	return (fd);
}
