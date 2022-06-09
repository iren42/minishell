/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 18:10:23 by iren              #+#    #+#             */
/*   Updated: 2022/04/29 16:19:05 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last_element;

	if (*alst == 0)
	{
		*alst = new;
	}
	else
	{
		last_element = ft_lstlast(*alst);
		last_element->next = new;
	}
}
