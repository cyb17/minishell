/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ressources.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:30:35 by yachen            #+#    #+#             */
/*   Updated: 2023/12/02 13:26:37 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

// Free int **pipefd
void	free_pipefd(int **pipefd, int nb_pipe)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
		free(pipefd[i++]);
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
			{
				close(tab->pipefd[i - 1][0]);
				close(tab->pipefd[i - 1][1]);
			}
			return (-1);
		}
	}
	return (0);
}

// Return nb of process
int	find_nb_process(t_process *prcs)
{
	int			nb_process;
	t_process	*process;

	nb_process = 0;
	process = prcs;
	while (process)
	{
		nb_process++;
		process = process->next;
	}
	return (nb_process);
}

// Initialize struct t_tab's data and malloc necessary space if need
// Return NULL if malloc failed
t_tab	*fill_tab(t_process *process)
{
	t_tab	*tab;
	int		i;

	tab = (t_tab *)malloc(sizeof(t_tab));
	if (!tab)
	{
		ft_putstr_fd("Error: fill_tab: tab malloc failed\n", 2);
		return (NULL);
	}
	tab->nb_pipe = find_nb_process(process) - 1;
	tab->pipefd = (int **)malloc(sizeof(int *) * (tab->nb_pipe));
	if (!(tab->pipefd))
	{
		ft_putstr_fd("Error: fill_tab: pipefd: malloc failed\n", 2);
		free(tab);
		return (NULL);
	}
	i = 0;
	while (i < tab->nb_pipe)
	{
		tab->pipefd[i] = (int *)malloc(sizeof(int) * 2);
		if (!(tab->pipefd[i]))
		{
			ft_putstr_fd("Error: fill_tab: pipefd[i]: malloc failed\n", 2);
			free_pipefd(tab->pipefd, i);
			free(tab);
			return (NULL);
		}
		i++;
	}
	return (tab);
}

// Initialize and fill struct t_builtins's data
t_builtins	*fill_builtins(char **env)
{
	t_builtins	*builtins;

	builtins = (t_builtins *)malloc(sizeof(t_builtins));
	if (!builtins)
		return (NULL);
	builtins->envlist = env_to_envlist(env);
	if (!builtins->envlist && env[0])
	{
		free(builtins);
		return (NULL);
	}
	builtins->explist = env_to_envlist(env);
	if (!builtins->explist && env[0])
	{
		clear_lst(&builtins->envlist);
		free(builtins);
		return (NULL);
	}
	builtins->arg = NULL;
	return (builtins);
}
