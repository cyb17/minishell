/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:23:24 by yachen            #+#    #+#             */
/*   Updated: 2023/12/02 15:18:23 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

// Error = 1 || succes = 0
int	ft_env(char **arg, t_list *envlist)
{
	t_list	*tmp;

	tmp = envlist;
	if (arg[1] != NULL)
	{
		ft_putstr_fd("Error: env: too many arguments\n", 2);
		return (1);
	}
	while (tmp != NULL)
	{
		if (printf("%s\n", (char *)tmp->content) < 0)
		{
			perror("Error: env: printf: ");
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
