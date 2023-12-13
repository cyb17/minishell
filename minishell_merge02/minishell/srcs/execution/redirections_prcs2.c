/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_prcs2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:30:43 by yachen            #+#    #+#             */
/*   Updated: 2023/12/13 17:31:33 by yachen           ###   ########.fr       */
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
	}
	if (fdout != STDOUT_FILENO)
	{
		if (dup2(fdout, STDOUT_FILENO) == -1)
			ft_perror("Error: redir_first_process: dup2: fdout", &rslt);
	}
	else
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			ft_perror("Error: redir_first_process: dup2: pipefd[1]", &rslt);
	}
	clean_fdin_fdout(fdin, fdout);
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
	}
	clean_fdin_fdout(fdin, fdout);
	close(pipefd[0]);
	return (rslt);
}

static int	redir_medium_prcs(int fdin, int fdout, int *previous, int *current)
{
	int	rslt;

	rslt = 0;
	if (fdin != STDIN_FILENO)
	{
		if (dup2(fdin, STDIN_FILENO) == -1)
			ft_perror("Error: redir_medium_prcs: dup2: fdin", &rslt);
	}
	else
	{
		if (dup2(previous[0], STDIN_FILENO) == -1)
			ft_perror("Error: redir_medium_prcs: dup2: previous[0]", &rslt);
	}
	if (fdout != STDOUT_FILENO)
	{
		dup2(fdout, STDOUT_FILENO);
			ft_perror("Error: redir_medium_prcs: dup2: fdout", &rslt);
	}
	else
	{
		dup2(current[1], STDOUT_FILENO);
			ft_perror("Error: redir_medium_prcs: dup2: current[1]", &rslt);
	}
	clean_fdin_fdout(fdin, fdout);
	close(previous[0]);
	close(current[1]);
	return (rslt);
}

// static void	redir_medium_prcs(int fdin, int fdout, int *previous, int *current)
// {
// 	close(current[0]);
// 	if (fdin != STDIN_FILENO)
// 	{
// 		dup2(fdin, STDIN_FILENO);
// 		close(fdin);
// 		close(previous[0]);
// 	}
// 	else
// 	{
// 		dup2(previous[0], STDIN_FILENO);
// 		close(previous[0]);
// 	}
// 	if (fdout != STDOUT_FILENO)
// 	{
// 		dup2(fdout, STDOUT_FILENO);
// 		close(fdout);
// 		close(current[1]);
// 	}
// 	else
// 	{
// 		dup2(current[1], STDOUT_FILENO);
// 		close(current[1]);
// 	}
// }

int	redirection_multi_prcs(int fdin, int fdout, t_tab *tab, int i)
{
	int	rslt;

	if (i == 0)
	{
		if (redir_first_process(fdin, fdout, tab->pipefd[i]) == -1)
			return (-1);
	}
	else if (i == tab->nb_pipe)
	{
		if (redir_last_process(fdin, fdout, tab->pipefd[i - 1]) == -1)
		return (-1);
	}
	else
	{
		close(tab->pipefd[i][0]);
		rslt = redir_medium_prcs(fdin, fdout, tab->pipefd[i - 1], tab->pipefd[i]);
		clean_fdin_fdout(fdin, fdout);
		close(tab->pipefd[i - 1][0]);
		close(tab->pipefd[i][1]);
		if (rslt == -1)
			return (-1);
	}
	return (0);
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
