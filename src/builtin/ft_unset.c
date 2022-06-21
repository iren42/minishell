/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 05:12:41 by iren              #+#    #+#             */
/*   Updated: 2022/06/21 10:54:03 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*find_name_from_env(t_list *env_list, char *name) // return prev
{
	t_list	*l;
	t_list	*prev;

	if (env_list)
	{
		l = env_list;
		while (l)
		{
			if (ft_memcmp(get_env_name(l->content), name, ft_strlen(name) + 1) == 0)
				return (prev);
			prev = l;
			l = l->next;
		}
	}
	return (0);
}

char	*get_arg_value(void *o)
{
	t_arg	*a;

	a = (t_arg *)o;
	return (a->value);
}

int	ft_unset(t_cmdtab *c)
{
	t_list	*l1;
	t_list	*prev;
	char	*name;
	t_list	*tmp;

	if (c->m->env_list && c && c->arg_list)
	{
		l1 = c->arg_list;
		while (l1)
		{
			name = get_arg_value(l1->content);
		//		printf("name %s\n", name); 
			if (!is_syntax_ok(name))
			{
				printf("unset: `%s': not a valid identifier\n", name);
				return (FAILURE);

			}
			prev = find_name_from_env(c->m->env_list , name);
			if (prev)
			{
				//			print_env(prev->content);
				if (ft_memcmp(name, get_env_name(prev->next->content), ft_strlen(name) + 1) == 0)
				{
					// delete
					tmp = prev->next;
					//			printf("found\n"); 
					prev->next = prev->next->next;
					ft_lstdelone(tmp, del_env);
					return (SUCCESS);
				}
			}
			l1 = l1->next;
		}
	}
	return (SUCCESS);
}
