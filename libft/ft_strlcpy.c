/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 20:06:30 by iren              #+#    #+#             */
/*   Updated: 2022/04/29 17:31:42 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *s, size_t size)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (s[len])
		len++;
	if (size == 0)
		return (len);
	while ((s[i]) && --size)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}
