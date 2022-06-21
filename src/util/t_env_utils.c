/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:23:02 by iren              #+#    #+#             */
/*   Updated: 2022/06/21 20:12:10 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *name, t_list *env_list)
{
	t_list *l;

	l = env_list;
	if (env_list != 0 && name)
	{
		while (l)
		{
			if (ft_memcmp(get_env_name(l->content), name, ft_strlen(name) + 1) == 0)
			//	return (get_env_name(l->content) + ft_strlen(name) + 1);
				return (get_env_value(l->content));
			l = l->next;
		}
	}
	return (0);
}

t_env	*ft_getenv_ptr(char *name, t_list *env_list)
{
	t_list *l;

	l = env_list;
	if (env_list != 0 && name)
	{
		while (l)
		{
			if (ft_memcmp(get_env_name(l->content), name, ft_strlen(name) + 1) == 0)
				return (l->content);
			l = l->next;
		}
	}
	return (0);
}
void	del_env(void *o)
{
	t_env	*e;

	e = (t_env *)o;
	free(e->name);
	free(e->value);
	free(e);
}

char	*get_env_name(void *o)
{
	t_env	*e;

	e = (t_env *)o;
	//	printf("env name %s\n", e->name);
	return (e->name);
}

char	*get_env_value(void *o)
{
	t_env	*e;

	e = (t_env *)o;
	return (e->value);
}

int	is_syntax_ok(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && !ft_isdigit(s[i]))
			return (0);
		i++;
	}
	}
	return (1);
}


void	separate_name_value(t_env *e, char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
	{
		i++;
	}
	//	printf("s[i] %c, i %d\n", s[i], i);
}

t_env	*create_tenv(t_arg *a)
{
	int	len;
	t_env	*e;

	e = malloc(sizeof(t_env));
	if (!e)
		exit(1);
	e->value = 0;
	e->name = 0;
	len = get_len_env_name(a->value);
	e->name = ft_substr(a->value, 0, len);
	e->value = ft_substr(a->value, len + 1, ft_strlen(a->value));

	//	printf("get export value %s\n", s);
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
	//	printf("get export value %s\n", s);
	return (e);
}
