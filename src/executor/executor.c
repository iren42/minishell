/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <gufestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:28:08 by gufestin          #+#    #+#             */
/*   Updated: 2022/06/21 18:41:02 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_cmd(t_mini *mini, int cmd_num)
{
	char	**split_cmd;
	int		i;
	t_list	*tmp_arg_list;
	int	size;
	t_list	*tmp_cmdtab_list;

	tmp_cmdtab_list = mini->cmdtab_list;
	i = 0;
	while (i < cmd_num)
	{
		tmp_cmdtab_list = tmp_cmdtab_list->next;
		i++;
	}
	size = ft_lstsize(((t_cmdtab *)(tmp_cmdtab_list->content))->arg_list);
	split_cmd = (char **)malloc(sizeof(char *) * (size + 2));
	if (!split_cmd)
		exit(1); // malloc error
	split_cmd[0] = ((t_cmdtab *)(tmp_cmdtab_list->content))->cmd;
//	split_cmd[0] = ft_strdup("ls");
	tmp_arg_list = ((t_cmdtab *)(tmp_cmdtab_list->content))->arg_list;
	i = 1;
	while (i - 1 < size)
	{
		split_cmd[i] = ft_strdup(((t_arg *)(tmp_arg_list->content))->value);
		if (!split_cmd[i])
			exit(1); // malloc error
		i++;
		tmp_arg_list = tmp_arg_list->next;
	}
	split_cmd[i] = NULL;
	return (split_cmd);
}

char	**ft_split_env(t_mini *mini)
{
	char	**split_env;
	int		i;
	t_list	*tmp_list;
	int		size;
	char	*tmp;

	size = ft_lstsize(mini->env_list);
	split_env = (char **)malloc(sizeof(char *) * (size + 1));
	if (!split_env)
		exit(1); // malloc error
	i = 0;
	tmp_list = mini->env_list;
	while (i < size)
	{
		split_env[i] = ft_strjoin(((t_env *)(tmp_list->content))->name, "=");
		if (!split_env[i])
			exit(1); // malloc error
		tmp = split_env[i];
		split_env[i] = ft_strjoin(split_env[i], ((t_env *)(tmp_list->content))->value);
//		if (!split_env[i])
//			exit(1); // malloc error
		free(tmp);
		i++;
		tmp_list = tmp_list->next;
	}
	split_env[i] = NULL;
	return (split_env);
}

int	ft_exec(char **split_cmd, char **split_env, t_list *tmp_cmdtab_list)
{
	int		status;
	int		pipefd[2];
	pid_t	pid;

	status = 0;
	if (pipe(pipefd) == -1)
		exit(1); // pipe error
	pid = fork();
	if (pid == -1)
		exit(1); // fork error
	if (pid == 0)
	{
		close(pipefd[0]);
		execve(((t_cmdtab *)(tmp_cmdtab_list->content))->cmd, split_cmd, split_env);
		exit(126); // execve error
	}
	else
	{
		close(pipefd[1]);
		if (waitpid(pid, &status, 0) == -1)
			exit(1); // waitpid error
	}
	return (status);
}

int	executor(t_mini *mini)
{
//	pid_t	pid;
	int	status;
	char	**split_cmd;
	char	**split_env;
	int		nb_cmd;
	int		i;
	t_list	*tmp_cmdtab_list;

//	status = 0;
	split_env = ft_split_env(mini);
	nb_cmd = ft_lstsize(mini->cmdtab_list);
	tmp_cmdtab_list = mini->cmdtab_list;
	i = 0;
	while (i < nb_cmd)
	{
		split_cmd = ft_split_cmd(mini, i);
		status = ft_exec(split_cmd, split_env, tmp_cmdtab_list);
/*		pid = fork();
		if (pid == -1)
			exit(1); // fork error
		if (pid == 0)
		{
			execve(((t_cmdtab *)(tmp_cmdtab_list->content))->cmd, split_cmd, split_env);
			exit(126); // execve error
		}
		else
		{
			if (waitpid(pid, &status, 0) == -1)
				exit(1); // waitpid error
		}
*/		tmp_cmdtab_list = tmp_cmdtab_list->next;
//		free_split(split_cmd);
		i++;
	}
	free_split(split_env);
	return (status);
}
