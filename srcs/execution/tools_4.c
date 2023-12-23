/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:29:33 by yachen            #+#    #+#             */
/*   Updated: 2023/12/22 19:11:39 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

// Free int **pipefd
void	free_pipefd(int **pipefd, int nb_pipe)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
	{
		if (pipefd[i])
			free(pipefd[i++]);
	}
	free(pipefd);
}

// Pipe() pipefd[i]
int	pipe_pipefd(t_tab *tab, int i)
{
	if (i < tab->nb_pipe)
	{
		if ((pipe(tab->pipefd[i])) < 0)
		{
			if (i != 0)
				close(tab->pipefd[i - 1][0]);
			return (-1);
		}
	}
	return (0);
}

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
