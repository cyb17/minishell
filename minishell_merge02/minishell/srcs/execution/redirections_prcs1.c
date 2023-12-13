/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_prcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:30:43 by yachen            #+#    #+#             */
/*   Updated: 2023/12/13 16:42:56 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static void	ft_close(int fdin, int fdout, int pipefd, char *error_msg)
{
	if (error_msg)
		perror(error_msg);
	clean_fdin_fdout(fdin, fdout);
	close(pipefd);
}

static int dup2_stdin_stdout(int fd1, int fd2, int fd3, char indice)
{
	if (indice == 'I')
	{
		if (dup2(fd1, STDIN_FILENO) == -1)
			ft_close(fd1, fd2, fd3, "Error: dup2_stdin_stdout: stdin");
	}
	else if (indice == 'O')
	{
		
		if (dup2(fd1, STDOUT_FILENO) == -1)
			ft_close(fd1, fd2, fd3, "Error: dup2_stdin: stdout");
	}
}

static int	redir_first_process(int fdin, int fdout, int *pipefd)
{
	close(pipefd[0]);
	if (fdin != STDIN_FILENO)
	{
		if (dup2_stdin_stdout(fdin, fdout, pipefd[1], 'I') == -1)
			return (-1);
	}
	if (fdout != STDOUT_FILENO)
	{
		if (dup2_stdin_stdout(fdout, fdin, pipefd[1], 'O') == -1)
			return (-1);
	}
	else
	{
		if (dup2_stdin_stdout(pipefd[1], fdin, fdout, 'O') == -1)
			return (-1);
	}
	ft_close(fdin, fdout, pipefd[1], NULL);
	return (0);
}

static int	redir_last_process(int fdin, int fdout, int *pipefd)
{
	if (fdin != STDIN_FILENO)
	{
		if (dup2_stdin_stdout(fdin, fdout, pipefd[0], 'I') == -1)
			return (-1);
	}
	else
	{
		if (dup2_stdin_stdout(pipefd[0], fdin, fdout, 'I') == -1)
			return (-1);
	}
	if (fdout != STDOUT_FILENO)
	{
		dup2_stdin_stdout(fdout, fdin, pipefd[0], 'O');
			return (-1);
	}
	ft_close(fdin, fdout, pipefd[0], NULL);
	return (0);
}

static int	redir_medium_prcs(int fdin, int fdout, int *previous, int *current)
{
	close(current[0]);
	if (fdin != STDIN_FILENO)
	{
		dup2(fdin, STDIN_FILENO);
		close(fdin);
		close(previous[0]);
	}
	else
	{
		dup2(previous[0], STDIN_FILENO);
		close(previous[0]);
	}
	if (fdout != STDOUT_FILENO)
	{
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
		close(current[1]);
	}
	else
	{
		dup2(current[1], STDOUT_FILENO);
		close(current[1]);
	}
}

void	redirection_multi_prcs(int fdin, int fdout, t_tab *tab, int i)
{
	if (i == 0)
		redir_first_process(fdin, fdout, tab->pipefd[i]);
	else if (i == tab->nb_pipe)
		redir_last_process(fdin, fdout, tab->pipefd[i - 1]);
	else
		redir_medium_prcs(fdin, fdout, tab->pipefd[i - 1], tab->pipefd[i]);
}

// redirect io if there is a infile or outfile opened
int	redirection_single_prcs(int fdin, int fdout)
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
