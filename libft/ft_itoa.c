/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 21:12:13 by iren              #+#    #+#             */
/*   Updated: 2022/04/29 16:12:40 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(int n)
{
	int	res;

	res = 0;
	while (n != 0)
	{
		n = n / 10;
		res++;
	}
	return (res);
}

static char	*ft_zero(void)
{
	char	*res;

	res = malloc(sizeof(char) * (2));
	if (!res)
		return (0);
	res[0] = '0';
	res[1] = '\0';
	return (res);
}

static char	*copy(int count, long n)
{
	char	*res;

	res = malloc(sizeof(char) * (count + 1));
	if (!res)
		return (0);
	res[count] = '\0';
	count--;
	while (n != 0)
	{
		res[count--] = (n % 10 + '0');
		n = n / 10;
	}
	if (count == 0)
		res[count] = '-';
	return (res);
}

char	*ft_itoa(int nb)
{
	char	*res;
	int		count;
	long	n;

	n = (long)nb;
	count = ft_count_digits(n);
	if (count == 0)
		return (ft_zero());
	if (n < 0)
	{
		n *= (-1);
		count++;
	}
	res = copy(count, n);
	return (res);
}
