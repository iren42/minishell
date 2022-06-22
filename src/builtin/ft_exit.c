/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:07:54 by iren              #+#    #+#             */
/*   Updated: 2022/06/22 17:25:11 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_is_num(char	*value)
{
//	int	v;
	int	i;
//	int	sign;

	i = 0;
//	sign = 0;
//	printf("value %s\n", value);
	if (value[0] == '-' || value[0] == '+')
	{
//		sign = 1;
		i++;
	}
	while (value[i]) 
	{
		if (!ft_isdigit(value[i]))
			return (0);
		i++;
	}
//	if (i == 1 && sign == 0)
//		return (0);
//	v = ft_atoi(value);
	return (42);

}

int	ft_exit(t_cmdtab *c)
{
	t_mini *m;
	int	size;
	int	v;
	char	*value;

	if (c)
	{
		// exit should not work if arg_list != 0
	//	printf("argl size %d\n", ft_lstsize(c->arg_list));
		size = ft_lstsize(c->arg_list);
		if (size > 1)
		{
			print_error("shell: exit", NULL, 0, "too many arguments");
			return (FAILURE);
		}
		else if (size == 0)
		{
			printf("exit\n");
			exit(0);
		}
		else
		{
//	m = c->m;
			value = get_arg_value(c->arg_list->content);
			if (!str_is_num(value))
			{
				print_error("shell: exit", get_arg_value(c->arg_list->content), 0, "numeric argument required");
				exit(2);
			}
			v = ft_atoi(value);
			printf("exit\n");
			exit(v);
		}
/*		ft_lstclear(&m->token_list, del_token);
		ft_lstclear(&m->cmdtab_list, del_cmdtab);

		free(m->s);
		ft_lstclear(&m->env_list, del_env);
		rl_clear_history();
	*/	//exit(0);

	}
	return (SUCCESS);
}
