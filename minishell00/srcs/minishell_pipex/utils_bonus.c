/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:02:53 by yachen            #+#    #+#             */
/*   Updated: 2023/11/08 10:27:34 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

void	free_tab_int(t_tab *tab)
{
	int	i;

	i = 0;
	if (tab->pid)
		free(tab->pid);
	while (i < tab->nb_pipe)
	{
		if (tab->pipefd[i])
			free(tab->pipefd[i]);
		i++;
	}
	if (tab->pipefd)
		free(tab->pipefd);
}

void	ft_perror(char *str, int indice)
{
	if (indice == 1)
		perror("Error");
	if (str)
		ft_printf(": %s\n", str);
	exit(EXIT_FAILURE);
}

void	close_pipefd(int **pipefd, int nb_pipe, int i)
{
	int	j;

	j = 0;
	while (j <= i && j < nb_pipe)
	{
		close(pipefd[j][0]);
		close(pipefd[j][1]);
		j++;
	}
}

void	clean_all(t_tab *tab, int i, int indice)
{
	close(tab->fdin);
	close(tab->fdout);
	close_pipefd(tab->pipefd, tab->nb_pipe, i);
	if (indice == 1)
		free_tab_int(tab);
}

void	wait_proces(int j, int *pid, int nb_proces)
{
	int	i;
	int	status;

	i = 0;
	while (i < nb_proces && i < j)
		waitpid(pid[i++], &status, 0);
}
