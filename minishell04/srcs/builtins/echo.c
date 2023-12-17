/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:21:45 by yachen            #+#    #+#             */
/*   Updated: 2023/12/16 14:52:59 by achevala         ###   ########.fr       */
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

// // Error = 1 || succes = 0
// int	ft_echo(char **arg)
// {
// 	int	i;
// 	int	op_flag;

// 	i = 1;
// 	op_flag = 0;
// 	if (!arg[i])
// 		printf("\n");
// 	while (arg[i] && is_op(arg[i]) == 1)
// 	{
// 		op_flag = 1;
// 		i++;
// 	}
// 	if (!arg[i])
// 		return (0);
// 	while (arg[i])
// 		printf("%s ", arg[i++]);
// 	if (op_flag == 0)
// 		printf("\n");
// 	return (0);
// }

static int	print_echo_arg(char *argv)
{
	int	j;
	
	j = 0;
	
	while (argv[j])
	{
		/* if (argv[j + 1] && argv[j] == '$' && argv[j + 1] == '?')
		{
			ft_putnbr_fd(g_signal, STDOUT_FILENO);
			j++;
		}
		else */
			ft_putchar_fd(argv[j], STDOUT_FILENO);
		j++;
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
		if (print_echo_arg(arg[i]) == 1)
			return (1);
		if (arg[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (op_flag == 0)
		printf("\n");
	return (0);
}
