/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:43:16 by iren              #+#    #+#             */
/*   Updated: 2022/04/29 16:03:09 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_sub(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	char			*buffer;

	start = 0;
	buffer = 0;
	if (s1)
	{
		while (s1[start] && ft_strchr(set, (int)s1[start]))
			start++;
		end = ft_strlen(s1) - 1;
		while (s1[start] && s1[end] && ft_strrchr(set, (int)s1[end]))
			end--;
		buffer = ft_substr(s1, start, end - start + 1);
		if (!buffer)
			return (0);
	}
	return (buffer);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*final;

	final = 0;
	if (s1 == 0)
		return (final);
	if (set == 0)
		return (ft_strdup(s1));
	final = ft_sub(s1, set);
	if (!final)
		return (0);
	return (final);
}
