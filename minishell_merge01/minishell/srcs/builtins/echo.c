/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:21:45 by yachen            #+#    #+#             */
/*   Updated: 2023/12/02 15:17:49 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	is_op(char *str)
{
	if (*str == '-')
	{	
		str++;
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

static int	print_newline(void)
{
	if (printf("\n") == -1)
	{
		perror("Error: echo: ");
		return (1);
	}
	return (0);
}

static int	print_echo_arg(char **arg, int i, int op_flag)
{
	while (arg[i + 1])
	{
		if (printf("%s ", arg[i]) < 0)
		{
			perror("Error: echo: print_echo_arg: ");
			return (1);
		}
		i++;
	}
	if (printf("%s", arg[i]) < 0)
	{
		perror("Error: echo: print_echo_arg: ");
		return (1);
	}
	if (op_flag == 0)
	{
		if (print_newline() == 1)
			return (1);
	}
	return (0);
}

// Error = 1 || succes = 0
int	ft_echo(char **arg)
{
	int	i;
	int	op_flag;

	i = 1;
	op_flag = 0;
	if (arg[i] == NULL)
	{
		if (print_newline() == 1)
			return (1);
		return (0);
	}
	while (arg[i] && is_op(arg[i]) == 1)
	{
		op_flag = 1;
		i++;
	}
	if (!arg[i])
		return (0);
	if (print_echo_arg(arg, i, op_flag) == 1)
		return (1);
	return (0);
}
