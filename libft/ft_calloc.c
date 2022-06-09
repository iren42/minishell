/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 21:12:46 by iren              #+#    #+#             */
/*   Updated: 2022/04/29 17:35:21 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*s;

	if (nmemb == 0 || size == 0)
	{
		s = malloc(1);
		if (!s)
			return (0);
		return ((void *)s);
	}
	if (size == SIZE_MAX && nmemb == SIZE_MAX)
		return (0);
	s = malloc(size * nmemb);
	if (!s)
		return (0);
	ft_bzero(s, size * nmemb);
	return ((void *)s);
}
