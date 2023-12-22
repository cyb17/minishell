/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:29:33 by yachen            #+#    #+#             */
/*   Updated: 2023/12/22 13:37:58 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	isnot_builtins(char *str)
{
	if ((ft_strcmp("echo", str) == 1) || (ft_strcmp("cd", str) == 1)
		|| (ft_strcmp("env", str) == 1) || (ft_strcmp("exit", str) == 1)
		|| (ft_strcmp("export", str) == 1) || (ft_strcmp("unset", str) == 1)
		|| (ft_strcmp("pwd", str) == 1))
		return (0);
	return (1);
}

void	ft_ctrl_d(void)
{
	g_signal = 0;
	printf("exit\n");
	exit(g_signal);
}