/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:07:54 by iren              #+#    #+#             */
/*   Updated: 2022/06/25 02:34:43 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_is_num(char	*value)
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

static void	error_str_num(t_cmdtab *c)
{
	printf("exit\n");
	print_error("shell: exit", get_arg_value(c->arg_list->content), 0,
		"numeric argument required");
	g_errno = 2;
	exit(2);
}

static int	error_size(void)
{
	printf("exit\n");
	print_error("shell: exit", NULL, 0, "too many arguments");
	g_errno = 1;
	return (FAILURE);
}

int	ft_exit(t_cmdtab *c)
{
	int		size;
	char	*value;

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
			error_str_num(c);
		if (size > 1)
			return (error_size());
		g_errno = ft_atoi(value);
	}
	printf("exit\n");
	exit(g_errno);
	return (42);
}
