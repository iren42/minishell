/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoil.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:52:41 by iren              #+#    #+#             */
/*   Updated: 2022/04/29 16:13:32 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoil(const char *s)
{
	long long	res;
	int			i;
	int			minus;

	res = 0;
	i = 0;
	minus = 1;
	while ((s[i] >= '\t' && s[i] <= '\r') || s[i] == ' ')
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			minus *= (-1);
		i++;
	}
	while (s[i] && (s[i] >= '0' && s[i] <= '9'))
	{
		res = res * 10 + s[i] - '0';
		i++;
	}
	if (res > 2147483647 && minus > 0)
		return (2147483650);
	if (res > 2147483648 && minus < 0)
		return (-2147483650);
	return (minus * res);
}
