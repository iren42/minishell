/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:03:51 by iren              #+#    #+#             */
/*   Updated: 2022/04/29 16:06:35 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			*s;
	char			*d;
	unsigned int	i;

	i = 0;
	s = (char *)src;
	d = (char *)dest;
	if (d == s)
		return ((void *)d);
	if (s > d)
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (n--)
			d[n] = s[n];
	}
	return ((void *)d);
}
