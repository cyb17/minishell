/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:33:57 by yachen            #+#    #+#             */
/*   Updated: 2023/11/08 10:27:34 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

int	creat_pipefd(int i, int argc, int **pipefd)
{
	if (i < argc - 4)
	{
		if ((pipe(pipefd[i])) < 0)
		{
			if (i != 0)
				close(pipefd[i - 1][0]);
			return (-1);
		}
	}
	return (0);
}

void	ft_init_tab(t_tab *tab, int argc)
{
	int	i;

	i = 0;
	tab->nb_pipe = argc - 4;
	tab->pid = (int *)malloc(sizeof(int) * (argc - 3));
	if (!(tab->pid))
		ft_perror("Error : tab_pid\n", 0);
	tab->pipefd = (int **)malloc(sizeof(int *) * (argc - 4));
	if (!(tab->pipefd))
	{
		free(tab->pid);
		ft_perror("Error : tab_pipefd\n", 0);
	}
	while (i < argc -4)
	{
		tab->pipefd[i] = (int *)malloc(sizeof(int) * 2);
		if (!(tab->pipefd[i]))
		{
			free_tab_int(tab);
			ft_perror("Error : tab_pipefd\n", 0);
		}
		i++;
	}
}
