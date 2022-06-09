/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 20:28:44 by iren              #+#    #+#             */
/*   Updated: 2022/04/29 16:13:13 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	t_dest;
	size_t	t_src;
	size_t	j;
	char	*ssrc;

	t_dest = ft_strlen(dest);
	t_src = ft_strlen(src);
	j = 0;
	ssrc = (char *)src;
	if (t_dest >= size)
		return (t_src + size);
	size -= t_dest;
	while (ssrc[j] != '\0' && --size)
	{
		dest[t_dest + j] = ssrc[j];
		j++;
	}
	dest[t_dest + j] = '\0';
	return (t_dest + t_src);
}
