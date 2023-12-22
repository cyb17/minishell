/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:21:45 by yachen            #+#    #+#             */
/*   Updated: 2023/12/22 19:04:03 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	is_op(char *str)
{
	if (*str == '-')
	{	
		str++;
		if (*str == '\0')
			return (0);
		while (*str)
		{
			if (*str != 'n')
				return (0);
			str++;
		}
	}
	else
		return (0);
	return (1);
}

// Error = 1 || succes = 0
int	ft_echo(char **arg)
{
	int	i;
	int	op_flag;

	i = 1;
	op_flag = 0;
	if (!arg[i])
		printf("\n");
	while (arg[i] && is_op(arg[i]) == 1)
	{
		op_flag = 1;
		i++;
	}
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (arg[i + 1])
			printf("%s ", arg[i++]);
		else
			printf("%s", arg[i++]);
	}
	if (op_flag == 0)
		printf("\n");
	return (0);
}
