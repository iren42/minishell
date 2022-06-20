/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <gufestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:28:08 by gufestin          #+#    #+#             */
/*   Updated: 2022/06/21 00:14:21 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_cmd(t_mini *mini)
{
	char	**split_cmd;
	int		i;
	t_list	*temp;
	int	size;

	size = ft_lstsize(mini->token_list);
	split_cmd = (char **)malloc(sizeof(char *) * (size + 1));
	if (!split_cmd)
	{
		//free_all()
		exit(1);
	}
	i = 0;
	temp = mini->token_list;
	while (i < size - 1)
	{
		split_cmd[i] = ft_strdup(((t_token *)(temp->content))->value);
		if (!split_cmd[i])
		{
			//free_all()
			exit(1);
		}
		i++;
		temp = temp->next;
	}
	split_cmd[i] = NULL;
	return (split_cmd);
}

int	executor(t_mini *mini)
{
	pid_t	pid;
	int	status;
	char	**split_cmd;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		//free_all()
		exit(1);
	}
	split_cmd = ft_split_cmd(mini);
	if (pid == 0)
	{
		execve(((t_cmdtab *)(mini->cmdtab_list->content))->cmd, split_cmd, mini->env);
		exit(126);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			exit(1);
	}
	return (status);
}
