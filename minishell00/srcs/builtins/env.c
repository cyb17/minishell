/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:23:24 by yachen            #+#    #+#             */
/*   Updated: 2023/10/30 16:30:04 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

void	ft_env(t_list *envlist)
{
	t_list	*tmp;

	tmp = envlist;
	while (tmp != NULL)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}
