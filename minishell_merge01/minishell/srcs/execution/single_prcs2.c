/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_prcs2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:14:10 by yachen            #+#    #+#             */
/*   Updated: 2023/12/06 14:19:51 by yachen           ###   ########.fr       */
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

static void	init_data(int *fdin, int *fdout, int *status)
{
	*fdin = STDIN_FILENO;
	*fdout = STDOUT_FILENO;
	*status = 0;
}

static void	child_prcs(t_res *res, t_tokens *cmd)
{
	int	fdin;
	int	fdout;
	int	status;

	init_data(&fdin, &fdout, &status);
	res->prcs->pid = fork();
	if (res->prcs->pid == -1)
	{
		perror("Error : fork");
		g_signal[0] = 1;
		return ;
	}
	else if (res->prcs->pid == 0)
	{
		if (open_fdin_fdout(&fdin, &fdout, res->prcs->list_tokens) == -1
		|| redirection_single_prcs(fdin, fdout) == -1)
		{
			clean_fds(fdin, fdout);
			garbage_collector_child(res);
			exit(1);
		}
		if (exe_no_builtins(res, cmd) == -1)
		{
			garbage_collector_child(res);
			exit(1);
		}
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

static void	clean_io(t_redir *io)
{
	if (io->fdin != STDIN_FILENO)
		close(io->fdin);
	if (io->fdout != STDOUT_FILENO)
		close(io->fdout);
	close(io->stdin);
	close(io->stdout);
}

int	init_stdin_stdout(int stdin, int stdout)
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
		clean_io(&io);
		garbage_collector_parent(res);
		return (1);
	}
	rslt = exe_builtins(res, cmd);
	init_stdin_stdout(io.stdin, io.stdout);
	return (rslt);
}

// If there is a infile or a outfile valid fd opened, close it.
void	clean_fds(int fdin, int fdout)
{
	if (fdin != STDIN_FILENO && fdin != -1)
		close(fdin);
	if (fdout != STDOUT_FILENO && fdout != -1)
		close(fdout);
}

// Browse tokens list, and fixe the fdin and fdout at the end of browse
// if <infile is found it's will be opened
// if there is another <infile the precedent will be closed and fdin=newone
// same for outfile
int	open_fdin_fdout(int *fdin, int *fdout, t_tokens *tokens)
{
	char	*here_doc;

	while (tokens)
	{
		if (tokens->type == REDIR_IN && tokens->next->type == INFILE)
			redirect_in(fdin, tokens->next->value);
		else if (tokens->type == REDIR_OUT && tokens->next->type == OUTFILE)
			redirect_out(fdout, tokens->next->value, 'T');
		else if (tokens->type == APPEN && tokens->next->type == OUTFILE)
			redirect_out(fdout, tokens->next->value, 'A');
		else if (tokens->type == HEREDOC)
		{
			here_doc = ft_here_doc(tokens->next->value);
			redirect_in(fdin, here_doc);
			free(here_doc);
		}
		if ((*fdin == -1) || (*fdout == -1))
			return (-1);
		tokens = tokens->next;
	}
	return (0);
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
