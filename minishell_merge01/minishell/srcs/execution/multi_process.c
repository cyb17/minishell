/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:14:40 by yachen            #+#    #+#             */
/*   Updated: 2023/12/08 17:05:49 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static void	error_task(int fdin, int fdout, t_res *res, int exit_code)
{
	clean_fds(fdin, fdout);
	garbage_collector_child(res);
	exit(exit_code);
}

static void	execute_cmd(t_res *res, t_tokens *list_tokens)
{
	t_tokens	*cmd;
	int			exit_code;

	cmd = check_cmd_tk(list_tokens);
	if (!cmd)
		return ;
	if (isnot_builtins(cmd->value) == 1)
	{
		if (exe_no_builtins(res, cmd) == -1)
		{
			garbage_collector_child(res);
			exit(1);
		}
	}
	else
	{
		exit_code = exe_builtins(res, cmd);
		exit(exit_code);
	}
}

static void	parent_task(t_tab *tab, int i, t_process *prcs, int *status)
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
	waitpid(prcs->pid, status, 0);
	if (WIFEXITED(*status))
		g_signal[0] = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		g_signal[0] = WTERMSIG(*status);
}

static void	exe_prcs(t_res *res, t_process *prcs, int i)
{
	int			fdin;
	int			fdout;
	int			status;

	fdin = STDIN_FILENO;
	fdout = STDOUT_FILENO;
	status = 0;
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
			error_task(fdin, fdout, res, 1);
		redirection_multi_prcs(fdin, fdout, res->tab, i);
		if (check_cmd_tk(prcs->list_tokens) == NULL)
			error_task(fdin, fdout, res, 0);
		execute_cmd(res, prcs->list_tokens);
	}
	else
		parent_task(res->tab, i, prcs, &status);
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
}
