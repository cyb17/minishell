/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:11:45 by yachen            #+#    #+#             */
/*   Updated: 2023/12/23 18:34:01 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_l)
{
	t_list	*tmp;

	if (*lst == NULL)
	{
		*lst = new_l;
		return ;
	}
	tmp = *lst;
	while (tmp -> next != NULL)
		tmp = tmp -> next;
	tmp -> next = new_l;
}
