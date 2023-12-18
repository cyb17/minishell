/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:47:35 by yachen            #+#    #+#             */
/*   Updated: 2023/12/18 17:49:30 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static long	minishell_atoi(const char *str)
{
	int		i;
	long	nb;
	int		sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] && (str[i] == ' ' || ((str[i] > 8 && str[i] < 14))))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}

// Check if is a numerique number between LLONG_MIN and LLONG_MAX
static int	is_numerique_arg(char *arg)
{
	int		i;
	long	nb;
	char	*tmp;
	
	i = 0;
	nb = 0;
	while (arg[i] && (arg[i] == ' ' || ((arg[i] > 8 && arg[i] < 14))))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
			return (-1);
		i++;
	}
	nb = minishell_atoi(arg);
	tmp = ft_itoa(nb);
	if (ft_strcmp(tmp, arg) == 0)
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (0);
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

static void	exit_succes(t_res *res, char **arg)
{
	g_signal = minishell_atoi(arg[1]) % 256;
	if (res->io)
		init_stdin_stdout(res->io->stdin, res->io->stdout);
	garbage_collector_child(res);
	exit(g_signal);
}

// Error = (1 || 2) || succes = exit(nb % 256)
int	ft_exit(char **arg, t_res *res)
{
	if (arg[1] == NULL)
	{
		if (res->io)
			init_stdin_stdout(res->io->stdin, res->io->stdout);
		garbage_collector_child(res);
		exit(g_signal = 0);
	}
	if (is_numerique_arg(arg[1]) == -1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		if (res->io)
			init_stdin_stdout(res->io->stdin, res->io->stdout);
		garbage_collector_child(res);
		exit(g_signal = 2);
	}
	if (check_nb_arg(arg) == -1)
	{
		garbage_collector_parent(res);
		return (g_signal = 1);
	}
	exit_succes(res, arg);
	return (0);
}
