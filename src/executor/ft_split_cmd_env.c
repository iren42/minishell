/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:48:36 by gufestin          #+#    #+#             */
/*   Updated: 2022/06/25 00:44:27 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_cmd_init(int size, t_list *tmp_cmdtab_list)
{
	char	**split_cmd;

	split_cmd = (char **)malloc(sizeof(char *) * (size + 2));
	if (!split_cmd)
		exit(1);
	split_cmd[0] = 0;
	if (((t_cmdtab *)(tmp_cmdtab_list->content))->cmd)
		split_cmd[0] = ft_strdup(((t_cmdtab *)(tmp_cmdtab_list->content))->cmd);
	else
		split_cmd[0] = ft_strdup("");
	if (!split_cmd[0])
		exit(1);
	return (split_cmd);
}

char	**ft_split_cmd(t_mini *mini, int cmd_num)
{
	char	**split_cmd;
	int		i;
	t_list	*tmp_arg_list;
	int		size;
	t_list	*tmp_cmdtab_list;

	tmp_cmdtab_list = mini->cmdtab_list;
	i = 0;
	while (i++ < cmd_num)
		tmp_cmdtab_list = tmp_cmdtab_list->next;
	size = ft_lstsize(((t_cmdtab *)(tmp_cmdtab_list->content))->arg_list);
	split_cmd = split_cmd_init(size, tmp_cmdtab_list);
	tmp_arg_list = ((t_cmdtab *)(tmp_cmdtab_list->content))->arg_list;
	i = 1;
	while (i - 1 < size)
	{
		split_cmd[i] = ft_strdup(((t_arg *)(tmp_arg_list->content))->value);
		if (!split_cmd[i])
			exit(1);
		i++;
		tmp_arg_list = tmp_arg_list->next;
	}
	split_cmd[i] = NULL;
	return (split_cmd);
}

char	**split_env_init(int *size, t_mini *mini)
{
	char	**split_env;

	*size = ft_lstsize(mini->env_list);
	split_env = (char **)malloc(sizeof(char *) * (*size + 1));
	if (!split_env)
		exit(1);
	return (split_env);
}

char	**ft_split_env(t_mini *mini)
{
	char	**split_env;
	int		i;
	t_list	*tmp_list;
	int		size;
	char	*tmp;

	split_env = split_env_init(&size, mini);
	i = 0;
	tmp_list = mini->env_list;
	while (i < size)
	{
		split_env[i] = ft_strjoin(((t_env *)(tmp_list->content))->name, "=");
		if (!split_env[i])
			exit(1);
		tmp = split_env[i];
		split_env[i] = ft_strjoin(split_env[i],
				((t_env *)(tmp_list->content))->value);
		if (!split_env[i])
			exit(1);
		free(tmp);
		i++;
		tmp_list = tmp_list->next;
	}
	split_env[i] = NULL;
	return (split_env);
}
