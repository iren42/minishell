/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 01:02:47 by gufestin          #+#    #+#             */
/*   Updated: 2022/06/25 01:08:04 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_syntax_ok(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (!ft_isalpha(s[i]) && s[i] != '_')
				return (0);
			i++;
		}
	}
	return (1);
}

int	get_len_env_name(char *env)
{
	int	i;

	i = 0;
	if (env)
	{
		while (env[i])
		{
			if (env[i] == '=')
			{
				return (i);
			}
			i++;
		}
	}
	return (0);
}

t_env	*create_tenv(t_arg *a)
{
	int		len;
	t_env	*e;

	e = malloc(sizeof(t_env));
	if (!e)
		exit(1);
	e->value = 0;
	e->name = 0;
	len = get_len_env_name(a->value);
	if (len != 0)
	{
		e->name = ft_substr(a->value, 0, len);
		e->value = ft_substr(a->value, len + 1, ft_strlen(a->value));
	}
	else
	{
		del_env(e);
		return (0);
	}
	return (e);
}

t_env	*create_new_env(char *name, char *value)
{
	t_env	*e;

	e = malloc(sizeof(t_env));
	if (!e)
		exit(1);
	e->value = 0;
	e->name = 0;
	e->name = ft_strdup(name);
	e->value = ft_strdup(value);
	return (e);
}
