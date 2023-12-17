/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_multi_prcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:30:43 by yachen            #+#    #+#             */
/*   Updated: 2023/12/14 12:51:00 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static void	ft_perror(char *msg, int *rslt)
{
	*rslt = -1;
	perror(msg);
}

static int	redir_first_process(int fdin, int fdout, int *pipefd)
{
	int	rslt;
	
	rslt = 0;
	close(pipefd[0]);
	if (fdin != STDIN_FILENO)
	{
		if (dup2(fdin, STDIN_FILENO) == -1)
			ft_perror("Error: redir_first_process: dup2: fdin", &rslt);
		close(fdin);
	}
	if (fdout != STDOUT_FILENO)
	{
		if (dup2(fdout, STDOUT_FILENO) == -1)
			ft_perror("Error: redir_first_process: dup2: fdout", &rslt);
		close(fdout);
	}
	else
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			ft_perror("Error: redir_first_process: dup2: pipefd[1]", &rslt);
	}
	close(pipefd[1]);
	return (rslt);
}

static int	redir_last_process(int fdin, int fdout, int *pipefd)
{
	int	rslt;
	
	rslt = 0;
	if (fdin != STDIN_FILENO)
	{
		if (dup2(fdin, STDIN_FILENO) == -1)
			ft_perror("Error: redir_last_process: dup2: fdin", &rslt);
		close(fdin);
	}
	else
	{
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			ft_perror("Error: redir_last_process: dup2: pipefd[0]", &rslt);
	}
	if (fdout != STDOUT_FILENO)
	{
		if (dup2(fdout, STDOUT_FILENO) == -1)
			ft_perror("Error: redir_last_process: dup2: fdout", &rslt);
		close(fdout);
	}
	close(pipefd[0]);
	return (rslt);
}

static int	redir_medium_prcs(int fdin, int fdout, int *previous, int *current)
{
	static int	rslt;

	if (fdin != STDIN_FILENO)
	{
		if (dup2(fdin, STDIN_FILENO) == -1)
			ft_perror("Error: redir_medium_prcs: dup2: fdin", &rslt);
		close(fdin);
	}
	else
	{
		if (dup2(previous[0], STDIN_FILENO) == -1)
			ft_perror("Error: redir_medium_prcs: dup2: previous[0]", &rslt);
	}
	if (fdout != STDOUT_FILENO)
	{
		if (dup2(fdout, STDOUT_FILENO) == -1)
			ft_perror("Error: redir_medium_prcs: dup2: fdout", &rslt);
		close(fdout);
	}
	else
	{
		if (dup2(current[1], STDOUT_FILENO) == -1)
			ft_perror("Error: redir_medium_prcs: dup2: current[1]", &rslt);
	}
	return (rslt);
}

int	redirection_multi_prcs(int fdin, int fdout, t_tab *tab, int i)
{
	int	rslt;

	rslt = 0;
	if (i == 0)
		rslt = redir_first_process(fdin, fdout, tab->pipefd[i]);
	else if (i == tab->nb_pipe)
		rslt = redir_last_process(fdin, fdout, tab->pipefd[i - 1]);
	else
	{
		close(tab->pipefd[i][0]);
		rslt = redir_medium_prcs(fdin, fdout, tab->pipefd[i - 1], tab->pipefd[i]);
		close(tab->pipefd[i - 1][0]);
		close(tab->pipefd[i][1]);
	}
	return (rslt);
}
