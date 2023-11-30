/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_prcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:34:34 by yachen            #+#    #+#             */
/*   Updated: 2023/11/30 17:34:00 by yachen           ###   ########.fr       */
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
	if (fdout > 2)
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

static void	child_prcs(int fdin, int fdout, t_res *res, t_tokens *cmd)
{
	res->prcs->pid = fork();
	if (res->prcs->pid == -1)
	{
		clean_fds(fdin, fdout);
		garbage_collector_parent(res);
		perror("Error : fork");
		return ;
	}
	else if (res->prcs->pid == 0)
		exe_no_builtins(res, cmd);
	waitpid(res->prcs->pid, NULL, 0);
}

static int	save_stdin_stdout(int *stdin, int *stdout)
{
	*stdin = dup(STDIN_FILENO);
	if (*stdin == -1)
	{
		perror("Error: save_stdin_stdout: dup");
		return (-1);
	}
	*stdout = dup(STDOUT_FILENO);
	if (*stdout == -1)
	{
		perror("Error: save_stdin_stdout: dup");
		close(*stdin);
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

void	single_prcs(t_res *res)
{
	int			fdin;
	int			fdout;
	int			stdin;
	int			stdout;
	t_tokens	*cmd;

	fdin = STDIN_FILENO;
	fdout = STDOUT_FILENO;
	if (save_stdin_stdout(&stdin, &stdout) == -1)
		return ;
	if (check_fdin_fdout(&fdin, &fdout, res->prcs->list_tokens) == -1)
	{
		clean_fds(fdin, fdout);
		garbage_collector_parent(res);
		return ;
	}
	cmd = check_cmd_tk(res->prcs->list_tokens);
	if (!cmd || redirection_single_prcs(fdin, fdout) == -1)
		return ;
	if (isnot_builtins(cmd->value) == 1)
		child_prcs(fdin, fdout, res, cmd);
	else
		exe_builtins(res, cmd);
	printf("test\n");
	init_stdin_stdout(stdin, stdout);
}
