/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:07:54 by iren              #+#    #+#             */
/*   Updated: 2022/06/24 11:57:41 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_is_num(char	*value)
{
	int	i;

	i = 0;
	if (value[0] == '-' || value[0] == '+')
		i++;
	while (value[i]) 
	{
		if (!ft_isdigit(value[i]))
			return (0);
		i++;
	}
	return (42);

}

int	ft_exit(t_cmdtab *c)
{
	t_mini *m;
	int	size;
	char	*value;

	//	if (c) // utile quand SIGINT appelera ft_exit(NULL);
	//	{
	size = ft_lstsize(c->arg_list);
	if (size == 0)
	{
		printf("exit\n");
		exit(g_errno);
	}
	else if (size >= 1)
	{
		value = get_arg_value(c->arg_list->content);
		if (!str_is_num(value))
		{
			printf("exit\n");
			print_error("shell: exit", get_arg_value(c->arg_list->content), 0, "numeric argument required");
			g_errno = 2;
			exit(2);
		}
		if (size > 1)
		{
			printf("exit\n");
			print_error("shell: exit", NULL, 0, "too many arguments");
			g_errno = 1;
			return (FAILURE);
		}
		g_errno = ft_atoi(value);
	}
	//	}
	printf("exit\n");
	exit(g_errno);
	return (42);
}
