/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:47:35 by yachen            #+#    #+#             */
/*   Updated: 2023/11/27 16:46:27 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static long	minishell_atoi(char *str, int *sign)
{
	int			i;
	long		nb;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] == ' ' || ((str[i] > 8 && str[i] < 14))))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb);
}

static int	is_correct_number(char *arg)
{
	int		i;
	int		sign;
	long	nb;
	
	i = 0;
	sign = 1;
	nb = 0;
	while (arg[i] && (arg[i] == ' ' || ((arg[i] > 8 && arg[i] < 14))))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (ft_isdigit(arg[i] == 0))
			return (0);
		i++;
	}
	nb = minishell_atoi(arg, &sign);
	if ((sign == -1 && nb < LLONG_MIN)
		|| (sign == 1 && nb > LLONG_MAX))
		return (0);
	return (nb * sign);
}

static int	check_nb_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: exit: too any arguments\n", 2);
		return (-1);
	}
	return (0);
}

int	ft_exit(char **arg)
{
	if (arg[1] == NULL)
	{
		g_signal[0] = 0;
		return (0);
	}
	if (is_correct_number(arg[1]) && ft_strcmp(arg[1], "0") == 0)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd("numeric argument required\n", 2);
		g_signal[0] = 2;
		return (0);
	}
	if (check_nb_arg(arg) == -1)
		return (-1);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	t_tab	*tab;

// 	tab = NULL;
// 	argc += 1;
// 	ft_exit(argv, tab);
// 	return (0);
// }