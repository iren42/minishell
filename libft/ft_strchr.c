/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 14:35:20 by iren              #+#    #+#             */
/*   Updated: 2022/04/30 09:16:00 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*st;

	i = 0;
	st = (char *)s;
	while (c < 0)
		c += 256;
	while (c > 255)
		c -= 256;
	while (st[i])
	{
		if (c == st[i])
			return (&st[i]);
		i++;
	}
	if (c == '\0')
		return (&st[i]);
	return ((char *)0);
}
