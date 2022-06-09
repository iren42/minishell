/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 19:32:54 by iren              #+#    #+#             */
/*   Updated: 2022/04/29 17:51:13 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_split(char **split, int i)
{
	if (split != 0)
	{
		while (i >= 0)
			free(split[i--]);
		free(split);
	}
	split = 0;
}

static int	ft_nb_words(const char *s, char c)
{
	int	i;
	int	nb_w;

	i = 0;
	nb_w = 0;
	if (s != 0)
	{
		while (s[i])
		{
			while (s[i] == c && s[i])
				i++;
			if (s[i] != '\0' && s[i] != c)
				nb_w++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (nb_w);
}

static int	word_len(const char *s, int c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (s)
	{
		while (s[i] != c && s[i])
		{
			i++;
			len++;
		}
	}
	return (len);
}

static char	*ft_copy(const char *s, int len, int *to_set)
{
	int		i;
	char	*res;

	i = 0;
	res = malloc(sizeof(char) * (len + 1));
	if (!res || !s)
		return (0);
	while (i < len && s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = 0;
	*(to_set) += len;
	return (res);
}

char	**ft_split(char const *str, char c)
{
	int		len;
	int		i;
	int		id_word;
	char	**res;

	id_word = -1;
	i = 0;
	len = 0;
	res = malloc(sizeof(char *) * (ft_nb_words(str, c) + 1));
	if (!res)
		return (0);
	while (++id_word < ft_nb_words(str, c))
	{
		while (str[i] == c && str[i])
			i++;
		len = word_len(&str[i], c);
		res[id_word] = ft_copy(&str[i], len, &i);
		if (!res[id_word])
		{
			ft_free_split(res, id_word);
			return (0);
		}
	}
	res[id_word] = 0;
	return (res);
}
