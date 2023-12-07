/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:14:40 by yachen            #+#    #+#             */
/*   Updated: 2023/12/07 16:59:06 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	exe_prcs(t_res *res, t_process *prcs, int i)
{
	int			fdin;
	int			fdout;

	fdin = STDIN_FILENO;
	fdout = STDOUT_FILENO;
	prcs->pid = fork();
	if (prcs->pid == -1)
	{
		perror("Error: exe_prcs: fork failed");
		g_signal[0] = 1;
		return ;
	}
	else if (prcs->pid == 0)
	{
		if (open_fdin_fdout(&fdin, &fdout, prcs->list_tokens) == -1)
		{
			clean_fds(fdin, fdout);
			garbage_collector_child(res);
			exit(1);
		}
		redirection_multi_prcs(fdin, fdout, res->tab, i);
		execute_cmd(res, prcs->list_tokens);
		// close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}
	else
		close_pipeline_fds(res->tab, i);
}

void	close_pipeline_fds(t_tab *tab, int i)
{
	if (i == 0)
		close(tab->pipefd[i][1]);
	else if (i == tab->nb_pipe)
		close(tab->pipefd[i - 1][0]);
	else
	{
		close(tab->pipefd[i][1]);
		close(tab->pipefd[i - 1][0]);
	}
}

void	multi_prcs(t_res *res)
{
	int			i;
	t_process	*tmp;

	i = 0;
	tmp = res->prcs;
	res->tab = fill_tab(res->prcs);
	if (!res->tab)
	{
		g_signal[0] = 1;
		return ;
	}
	while (tmp)
	{
		if (pipe_pipefd(res->tab, i) == -1)
		{
			ft_putstr_fd("Error: pipe_pipefd: create pipe failed\n", 2);
			break ;
		}
		exe_prcs(res, tmp, i);
		tmp = tmp->next;
		i++;
	}
	tmp = res->prcs;
	while (tmp)
	{
		printf("%s : %d\n", tmp->section_cmd, tmp->pid);
		if (tmp->pid != -1)
			waitpid(tmp->pid, NULL, 0);
		printf("waitpit succes\n");
		tmp = tmp->next;
	}
}
