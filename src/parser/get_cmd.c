/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 20:53:42 by isabelle          #+#    #+#             */
/*   Updated: 2022/06/15 20:53:53 by isabelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_path(char **env)
{
	if (env != 0)
	{
		while (*env != 0)
		{
			if (ft_strncmp("PATH=", *env, 5) == 0)
				return (*env + 5);
			env++;
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

static char	**get_splitpaths(char **env)
{
	char	**res;
	char	*path;

	res = 0;
	path = find_path(env);
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

char	*get_cmd(char **env, char *cmd)
{
	char	*res;
	char	**splitpaths;
	int		i;

	init_get_cmd(&res, &splitpaths, &i);
	splitpaths = get_splitpaths(env);
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
