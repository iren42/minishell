/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 00:17:36 by iren              #+#    #+#             */
/*   Updated: 2022/04/29 16:00:43 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*res;
	t_list	*new_elem;

	res = 0;
	if (lst == 0 || f == 0)
		return (0);
	while (lst)
	{
		new_elem = ft_lstnew((*f)(lst->content));
		if (!new_elem)
		{
			ft_lstclear(&res, del);
			return (0);
		}
		ft_lstadd_back(&res, new_elem);
		lst = lst->next;
	}
	return (res);
}
