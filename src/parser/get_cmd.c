/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 20:53:42 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/24 02:14:15 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_path(t_list *env_list)
{
	t_list	*l;

	l = env_list;
	if (env_list != 0)
	{
		while (l)
		{
			if (ft_memcmp(get_env_name(l->content), "PATH", 5) == 0)
			{
				return (get_env_value(l->content));
			}
			l = l->next;
		}
	}
	return (0);
}

static void	init_get_cmd(char **res, char ***splitpaths, int *i)
{
	*res = 0;
	*splitpaths = 0;
	*i = 0;
}

static char	**get_splitpaths(t_list *env_list)
{
	char	**res;
	char	*path;

	res = 0;
	path = find_path(env_list);
	if (path == 0)
		return (0);
	res = ft_split(path, ':');
	if (!res)
		return (0);
	return (res);
}

static char	*join(int i, char **splitpaths, char *cmd)
{
	char	*tmp;
	char	*res;

	res = 0;
	tmp = ft_strjoin(splitpaths[i], "/");
	if (!tmp)
	{
		free_split(splitpaths);
		return (0);
	}
	res = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!res)
	{
		free_split(splitpaths);
		return (0);
	}
	return (res);
}

char	*get_cmd(t_list *env_list, char *cmd)
{
	char	*res;
	char	**splitpaths;
	int		i;

	if (!cmd || !env_list)
		return (0);
	init_get_cmd(&res, &splitpaths, &i);
	splitpaths = get_splitpaths(env_list);
	if (splitpaths != 0)
	{
		while (splitpaths[i])
		{
			res = join(i, splitpaths, cmd);
			if (!res)
				return (0);
			if (access(res, X_OK) == 0)
			{
				free_split(splitpaths);
				return (res);
			}
			free(res);
			i++;
		}
		free_split(splitpaths);
	}
	return (0);
}
