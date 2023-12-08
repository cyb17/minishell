/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_prcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:14:10 by yachen            #+#    #+#             */
/*   Updated: 2023/12/08 15:30:46 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

// static void	init_data(int *fdin, int *fdout, int *status)
// {
// 	*fdin = STDIN_FILENO;
// 	*fdout = STDOUT_FILENO;
// 	*status = 0;
// }

static void	sub_child_prcs(int *fdin, int *fdout, t_res *res, t_tokens *cmd)
{
	if (open_fdin_fdout(fdin, fdout, res->prcs->list_tokens) == -1
	|| redirection_single_prcs(*fdin, *fdout) == -1)
	{
		clean_fds(*fdin, *fdout);
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
	// init_data(&fdin, &fdout, &status);
	res->prcs->pid = fork();
	if (res->prcs->pid == -1)
	{
		perror("Error : fork");
		g_signal[0] = 1;
		return ;
	}
	else if (res->prcs->pid == 0)
	{
		sub_child_prcs(&fdin, &fdout, res, cmd);
		// if (open_fdin_fdout(&fdin, &fdout, res->prcs->list_tokens) == -1
		// || redirection_single_prcs(fdin, fdout) == -1)
		// {
		// 	clean_fds(fdin, fdout);
		// 	garbage_collector_child(res);
		// 	exit(1);
		// }
		// if (exe_no_builtins(res, cmd) == -1)
		// {
		// 	garbage_collector_child(res);
		// 	exit(1);
		// }
	}
	waitpid(res->prcs->pid, &status, 0);
	if (WIFEXITED(status))
		g_signal[0] = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_signal[0] = WTERMSIG(status);
}

static int	init_intput_output(t_redir *io)
{
	io->fdin = STDIN_FILENO;
	io->fdout = STDOUT_FILENO;
	io->stdin = dup(STDIN_FILENO);
	if (io->stdin == -1)
	{
		perror("Error: save_stdin_stdout: dup");
		return (-1);
	}
	io->stdout = dup(STDOUT_FILENO);
	if (io->stdout == -1)
	{
		perror("Error: save_stdin_stdout: dup");
		close(io->stdin);
		return (-1);
	}
	return (0);
}

// static void	clean_io(t_redir *io)
// {
// 	if (io->fdin != STDIN_FILENO)
// 		close(io->fdin);
// 	if (io->fdout != STDOUT_FILENO)
// 		close(io->fdout);
// 	close(io->stdin);
// 	close(io->stdout);
// }

static int	parent_prcs(t_res *res, t_tokens *cmd)
{
	t_redir	io;
	int		rslt;
	
	if (init_intput_output(&io) == -1)
		return (1);
	res->io = &io;
	if (open_fdin_fdout(&io.fdin, &io.fdout, res->prcs->list_tokens) == -1
		|| redirection_single_prcs(io.fdin, io.fdout) == -1)
	{
		// clean_io(&io);
		if (io.fdin != STDIN_FILENO)
			close(io.fdin);
		if (io.fdout != STDOUT_FILENO)
			close(io.fdout);
		close(io.stdin);
		close(io.stdout);
		garbage_collector_parent(res);
		return (1);
	}
	rslt = exe_builtins(res, cmd);
	init_stdin_stdout(io.stdin, io.stdout);
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
		if (open_fdin_fdout(&io.fdin, &io.fdout, res->prcs->list_tokens) == -1)
		{
			clean_fds(io.fdin, io.fdout);
			g_signal[0] = 1;
			return ;
		}
		clean_fds(io.fdin, io.fdout);
		g_signal[0] = 0;
	}
	else if (cmd && isnot_builtins(cmd->value) == 1)
		child_prcs(res, cmd);
	else if (cmd && isnot_builtins(cmd->value) == 0)
		g_signal[0] = parent_prcs(res, cmd);
}
