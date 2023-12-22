/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_prcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:14:10 by yachen            #+#    #+#             */
/*   Updated: 2023/12/22 13:40:02 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

// redirect io if there is a infile or outfile opened
static int	redirection_single_prcs(int fdin, int fdout)
{
	if (fdin != STDIN_FILENO)
	{
		if (dup2(fdin, STDIN_FILENO) == -1)
		{
			perror("Error: redirection_single_prcs: fdin: dup2");
			return (-1);
		}
		close(fdin);
	}
	if (fdout != STDOUT_FILENO)
	{
		if (dup2(fdout, STDOUT_FILENO) == -1)
		{
			perror("Error: redirection_single_prcs: fdout: dup2");
			return (-1);
		}
		close(fdout);
	}
	return (0);
}

static void	sub_child_prcs(int *fdin, int *fdout, t_res *res, t_tokens *cmd)
{
	if (open_fdin_fdout(fdin, fdout, res->prcs) == -1
		|| redirection_single_prcs(*fdin, *fdout) == -1)
	{
		clean_fdin_fdout(*fdin, *fdout);
		garbage_collector_child(res);
		exit(1);
	}
	if (exe_no_builtins(res, cmd) == -1)
	{
		garbage_collector_child(res);
		exit(1);
	}
}

static void	child_prcs(t_res *res, t_tokens *cmd)
{
	int	fdin;
	int	fdout;
	int	status;

	fdin = STDIN_FILENO;
	fdout = STDOUT_FILENO;
	status = 0;
	res->prcs->pid = fork();
	if (res->prcs->pid == -1)
	{
		perror("Error : child_prcs: fork");
		g_signal = 1;
		return ;
	}
	else if (res->prcs->pid == 0)
	{
		signal(SIGINT, signal_handler_child);
		sub_child_prcs(&fdin, &fdout, res, cmd);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(res->prcs->pid, &status, 0);
	fixe_child_exit_code(&status);
}

static int	parent_prcs(t_res *res, t_tokens *cmd)
{
	t_redir	io;
	int		rslt;

	if (init_io(&io) == -1)
		return (1);
	res->io = &io;
	if (open_fdin_fdout(&io.fdin, &io.fdout, res->prcs) == -1
		|| redirection_single_prcs(io.fdin, io.fdout) == -1)
	{
		clean_fdin_fdout(io.fdin, io.fdout);
		close(io.stdin);
		close(io.stdout);
		garbage_collector_parent(res);
		return (1);
	}
	rslt = exe_builtins(res, cmd);
	if (init_stdin_stdout(io.stdin, io.stdout) == -1)
		return (1);
	return (rslt);
}

void	single_prcs(t_res *res)
{
	t_redir		io;
	t_tokens	*cmd;

	cmd = check_cmd_tk(res->prcs->list_tokens);
	if (!cmd)
	{
		io.fdin = STDIN_FILENO;
		io.fdout = STDOUT_FILENO;
		if (open_fdin_fdout(&io.fdin, &io.fdout, res->prcs) == -1)
		{
			clean_fdin_fdout(io.fdin, io.fdout);
			g_signal = 1;
			return ;
		}
		clean_fdin_fdout(io.fdin, io.fdout);
		g_signal = 0;
	}
	else if (cmd && isnot_builtins(cmd->value) == 1)
		child_prcs(res, cmd);
	else if (cmd && isnot_builtins(cmd->value) == 0)
		g_signal = parent_prcs(res, cmd);
}
