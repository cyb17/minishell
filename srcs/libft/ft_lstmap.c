/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:14:15 by yachen            #+#    #+#             */
/*   Updated: 2023/05/16 15:14:17 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*anewlist;

	anewlist = NULL;
	while (lst != NULL)
	{
		newlist = ft_lstnew((*f)(lst -> content));
		if (newlist == NULL)
		{
			ft_lstclear(&anewlist, del);
			break ;
		}
		ft_lstadd_back(&anewlist, newlist);
		lst = lst -> next;
	}
	return (anewlist);
}
