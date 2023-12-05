/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_prcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:34:34 by yachen            #+#    #+#             */
/*   Updated: 2023/12/05 15:47:40 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static int	redirection_single_prcs(int fdin, int fdout)
{
	if (fdin != STDIN_FILENO)
	{
		if (dup2(fdin, STDIN_FILENO) == -1)
		{
			perror("Error: redirection_single_prcs: fdin: dup2");
			close(fdin);
			if (fdout != STDOUT_FILENO)
				close(fdout);
			return (-1);
		}
		close(fdin);
	}
	if (fdout != STDOUT_FILENO)
	{
		if (dup2(fdout, STDOUT_FILENO) == -1)
		{
			perror("Error: redirection_single_prcs: fdout: dup2");
			close(fdout);
			return (-1);
		}
		close(fdout);
	}
	return (0);
}

static int	child_prcs(t_redir *io, t_res *res, t_tokens *cmd)
{
	int	status;

	status = 0;
	res->prcs->pid = fork();
	if (res->prcs->pid == -1)
	{
		clean_fds(io->fdin, io->fdout);
		garbage_collector_parent(res);
		perror("Error : fork");
		return (1);
	}
	else if (res->prcs->pid == 0)
	{
		close(io->stdin);
		close(io->stdout);
		exe_no_builtins(res, cmd);
	}
	waitpid(res->prcs->pid, &status, 0);
	if (WIFEXITED(status))
		g_signal[0] = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_signal[0] = WTERMSIG(status);
	return (0);
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

static int	init_stdin_stdout(int stdin, int stdout)
{
	if (dup2(stdin, STDIN_FILENO) == -1)
	{
		perror("Error: init_stdin_stdout: dup2");
		close(stdin);
		close(stdout);
		return (-1);
	}
	close(stdin);
	if (dup2(stdout, STDOUT_FILENO) == -1)
	{
		perror("Error: init_stdin_stdout: dup2");
		close(stdin);
		close(stdout);
		return (-1);
	}
	close(stdout);
	return (0);
}

// Return command's exit value
int	single_prcs(t_res *res)
{
	t_redir		io;
	t_tokens	*cmd;
	int			rslt;

	if (init_intput_output(&io) == -1)
		return (1);
	if (open_fdin_fdout(&io.fdin, &io.fdout, res->prcs->list_tokens) == -1)
	{
		clean_fds(io.fdin, io.fdout);
		garbage_collector_parent(res);
		return (1);
	}
	cmd = check_cmd_tk(res->prcs->list_tokens);
	if (!cmd)
		return (0);
	if (redirection_single_prcs(io.fdin, io.fdout) == -1)
		return (1);
	if (isnot_builtins(cmd->value) == 1)
		rslt = child_prcs(&io, res, cmd);
	else
		rslt = exe_builtins(res, cmd);
	init_stdin_stdout(io.stdin, io.stdout);
	return (rslt);
}
