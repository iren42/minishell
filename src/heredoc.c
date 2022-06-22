/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <gufestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 23:56:04 by gufestin          #+#    #+#             */
/*   Updated: 2022/06/23 01:24:28 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//int	ft_heredoc(char *file, char *eof)
int	ft_heredoc(char *eof)
{
	int	fd;
	char	*filename;
	char	*read;
	int	eof_len;

//	filename = ft_strjoin(file, ".heredoc");
//	if (!filename)
//		exit(1); // malloc error
//	fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0664);
	fd = open(".heredoc", O_CREAT | O_RDWR | O_APPEND, 0664);
	if (fd == -1)
		exit(1); // open error
	eof_len = ft_strlen(eof);
	read = readline("> ");
	while (ft_strncmp(read, eof, eof_len))
	{
		ft_putstr_fd(read, fd);
		ft_putstr_fd("\n", fd);
		free(read);
		read = readline("> ");
	}
	free(read);
	close(fd);
//	fd = open(filename, O_RDONLY);
	free(filename);
//	return (fd);
	return (42);
}
