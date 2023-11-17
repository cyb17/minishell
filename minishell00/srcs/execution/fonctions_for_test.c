/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions_for_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:57:49 by yachen            #+#    #+#             */
/*   Updated: 2023/11/17 15:37:42 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_lst(t_list **list)
{
	t_list	*current;

	current = NULL;
	while (*list)
	{
		current = *list;
		*list = (*list)->next;
		free(current);
	}
}

t_list	*env_to_envlist(char **env)
{
	int		i;
	t_list	*envlist;
	t_list	*tmp;

	i = 0;
	envlist = NULL;
	while (env[i])
	{
		tmp = ft_lstnew(env[i]);
		if (!tmp)
		{
			clear_lst(&envlist);
			return (NULL);
		}
		ft_lstadd_back(&envlist, tmp);
		i++;
	}
	return (envlist);
}

int	find_nb_process(t_process *process)
{
	int	nb_process;

	nb_process = 0;
	while (process)
	{
		nb_process++;
		process = process->next;
	}
	return (nb_process);
}

void	free_pipefd(int **pipefd, int nb_pipe)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
		free(pipefd[i++]);
	free(pipefd);
}

int	pipe_pipefd(int **pipefd, int nb_pipe)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
	{
		if ((pipe(pipefd[i])) < 0)
		{
			perror("fill_tab: creat_pipefd");
			while (--i >= 0)
			{
				close(pipefd[i][0]);
				close(pipefd[i][1]);
			}
			free_pipefd(pipefd, i);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	creat_pipefd(t_tab *tab)
{
	int	i;

	i = 0;
	tab->pipefd = (int **)malloc(sizeof(int *) * (tab->nb_pipe));
	if (!(tab->pipefd))
	{
		ft_putstr_fd("fill_tab: malloc_pipefd: pipefd: malloc failed\n", 2);
		return (-1);
	}
	i = 0;
	while (i < tab->nb_pipe)
	{
		tab->pipefd[i] = (int *)malloc(sizeof(int) * 2);
		if (!(tab->pipefd[i]))
		{
			ft_putstr_fd("fill_tab: malloc_pipefd: []: malloc failed\n", 2);
			free_pipefd(tab->pipefd, i);
			return (-1);
		}
		i++;
	}
	if (pipe_pipefd(tab->pipefd, tab->nb_pipe) == -1)
		return (-1);
	return (0);
}

t_tab	*fill_tab(t_process *process)
{
	t_tab	*tab;

	tab = (t_tab *)malloc(sizeof(t_tab));
	if (!tab)
		return (NULL);
	tab->fdin = 0;
	tab->fdout = 0;
	tab->nb_pipe = find_nb_process(process) - 1;
	tab->tab_pid = (pid_t *)malloc(sizeof(pid_t) * (tab->nb_pipe + 1));
	if (!tab->tab_pid)
	{
		free(tab);
		ft_putstr_fd("fill_tab: tab_pid: malloc failed\n", 2);
		return (NULL);
	}
	ft_memset(tab->tab_pid, 0, tab->nb_pipe + 1);
	if (creat_pipefd(tab) == -1)
	{
		free(tab->tab_pid);
		free(tab);
		return (NULL);
	}
	return (tab);
}

t_builtins	*fill_builtins(char **env)
{
	t_builtins	*builtins;

	builtins = (t_builtins *)malloc(sizeof(t_builtins));
	if (!builtins)
		return (NULL);
	builtins->envlist = env_to_envlist(env);
	if (builtins->envlist == NULL)
	{
		free(builtins);
		return (NULL);
	}
	builtins->explist = env_to_envlist(env);
	if (builtins->explist == NULL)
	{
		clear_lst(&builtins->envlist);
		free(builtins);
		return (NULL);
	}
	builtins->arg = NULL;
	return (builtins);
}// fonction teste, no pb
