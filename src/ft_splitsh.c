/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitsh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 19:32:54 by iren              #+#    #+#             */
/*   Updated: 2022/06/25 01:06:57 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "minishell.h"

static char	**ft_free_split(char **split, int i)
{
	if (split != 0)
	{
		while (i >= 0)
			free(split[i--]);
		free(split);
	}
	split = 0;
	return ((char **)0);
}

static int	ft_nb_words(const char *s, const char *c)
{
	int	i;
	int	nb_w;
	int	q;

	i = 0;
	nb_w = 0;
	if (s != 0 && c)
	{
		while (s[i])
		{
			while (ft_strchr(c, s[i]) && s[i])
				i++;
			if (s[i] && !ft_strchr(c, s[i]))
			{
				nb_w++;
				if (!is_quote(s[i]))
				{
					while (s[i] && !ft_strchr(c, s[i]) && !is_quote(s[i]))
						i++;
				}
				else
				{
					q = s[i++];
					while (s[i] && s[i] != q)
						i++;
					i++;
				}
			}
		}
	}
	return (nb_w);
}

static int	word_len(const char *s, const char *c)
{
	int	i;
	int	len;
	int	q;

	i = 0;
	len = 0;
	if (s && c)
	{
		q = is_quote(s[i]);
		if (!q)
		{
			while (!ft_strchr(c, s[i]) && s[i] && !is_quote(s[i]))
			{
				i++;
				len++;
			}
		}
		else
		{
			i++;
			len++;
			while (s[i] && q != s[i])
			{
				i++;
				len++;
			}
			len++;
			if (q != s[i])
				ft_error(ERR_QUOTE, 1);
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

char	**ft_splitsh(char const *str, const char *c)
{
	int		len;
	int		i;
	int		id_word;
	char	**res;
	int		nb_w;

	id_word = -1;
	i = 0;
	len = 0;
	nb_w = ft_nb_words(str, c);
	res = malloc(sizeof(char *) * (nb_w + 1));
	if (!res)
		return (0);
	while (++id_word < nb_w)
	{
		while (ft_strchr(c, str[i]) && str[i])
			i++;
		len = word_len(&str[i], c);
		res[id_word] = ft_copy(&str[i], len, &i);
		if (!res[id_word])
			return (ft_free_split(res, id_word));
	}
	res[id_word] = 0;
	return (res);
}
*/
