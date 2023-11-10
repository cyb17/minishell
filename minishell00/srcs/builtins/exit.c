/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:47:35 by yachen            #+#    #+#             */
/*   Updated: 2023/11/10 16:23:41 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

int	ft_exit(char **arg, t_tab *tab)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (i > 1)
		{
			ft_putstr_fd("minishell: exit: too any arguments", 2);
			return (-1);
		}
		i++;
	}
	i = 0;
	while (arg[1][i])
	{
		if (ft_isdigit(arg[1][i]) == 0)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(arg[1], 2);
			ft_putstr_fd("numeric argument required", 2)
			garbage_collector(tab->process, tab, tab->builtins, tab->input);
			exit(2);
		}
		i++;
	}
	garbage_collector(tab->process, tab, tab->builtins, tab->input);
	exit(0);
}
