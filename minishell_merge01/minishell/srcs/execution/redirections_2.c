/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_multi_prcs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:30:43 by yachen            #+#    #+#             */
/*   Updated: 2023/12/07 17:10:27 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

//  PENSE A PROTEGER LES DUP2 !!

static void	redir_first_process(int fdin, int fdout, int *pipefd)
{
	close(pipefd[0]);
	if (fdin != STDIN_FILENO)
	{
		dup2(fdin, STDIN_FILENO);
		close(fdin);
	}
	if (fdout != STDOUT_FILENO)
	{
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
		close(pipefd[1]);
	}
	else
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
}

static void	redir_last_process(int fdin, int fdout, int *pipefd)
{
	if (fdin != STDIN_FILENO)
	{
		dup2(fdin, STDIN_FILENO);
		close(fdin);
		close(pipefd[0]);
	}
	else
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	if (fdout != STDOUT_FILENO)
	{
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
	}
}

static void	redir_medium_prcs(int fdin, int fdout, int *previous, int *current)
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
