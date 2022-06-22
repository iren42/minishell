/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:07:54 by iren              #+#    #+#             */
/*   Updated: 2022/06/22 14:54:50 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_is_num(char	*value)
{
	int	v;
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	printf("value %s\n", value);
	if (value[0] == '-' || value[0] == '+')
	{
		sign = 1;
		i++;
	}
	while (value[i]) 
	{
		if (!ft_isdigit(value[i]))
			return (0) ;
		i++;
	}
	if (i == 1 && sign == 0)
		return (0);
	v = ft_atoi(value);
	return (v);

}

int	ft_exit(t_cmdtab *c)
{
	t_mini *m;

	if (c)
	{
		// exit should not work if arg_list != 0
	//	printf("argl size %d\n", ft_lstsize(c->arg_list));
		if (ft_lstsize(c->arg_list) > 1)
		{
			print_error("shell: exit", NULL, 0, "too many arguments");
			return (FAILURE);
		}
	m = c->m;
	if (!str_is_num(get_arg_value(c->arg_list->content)))
			print_error("shell: exit", get_arg_value(c->arg_list->content), 0, "numeric argument required");
/*		ft_lstclear(&m->token_list, del_token);
		ft_lstclear(&m->cmdtab_list, del_cmdtab);

		free(m->s);
		ft_lstclear(&m->env_list, del_env);
		rl_clear_history();
	*/	exit(0);

	}
	return (SUCCESS);
}
