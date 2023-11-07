/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_case_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:08:27 by yachen            #+#    #+#             */
/*   Updated: 2023/09/09 14:17:52 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

pid_t	procs_fdin(int i, t_tab *tab, char **env, char *argv_value)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == -1)
	{
		perror("Error : fork");
		return (0);
	}
	else if (pid == 0)
	{
		path = child_procs_part_1(i, tab, env, argv_value);
		child_procs_part_2(i, tab, tab->fdin, tab->pipefd[i][1]);
		child_procs_part_3(path, argv_value);
	}
	else
	{
		close(tab->pipefd[i][1]);
		close(tab->fdin);
		return (pid);
	}
	return (0);
}

pid_t	procs_pipe(int i, t_tab *tab, char **env, char *argv_value)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == -1)
	{
		perror("Error : fork");
		return (0);
	}
	else if (pid == 0)
	{
		path = child_procs_part_1(i, tab, env, argv_value);
		child_procs_part_2(i, tab, tab->pipefd[i - 1][0], tab->pipefd[i][1]);
		child_procs_part_3(path, argv_value);
	}
	else
	{
		close(tab->pipefd[i - 1][0]);
		close(tab->pipefd[i][1]);
		return (pid);
	}
	return (0);
}

pid_t	procs_fdout(int i, t_tab *tab, char **env, char *argv_value)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == -1)
	{
		perror("Error : fork");
		return (0);
	}
	else if (pid == 0)
	{
		path = child_procs_part_1(i, tab, env, argv_value);
		child_procs_part_2(i, tab, tab->pipefd[i - 1][0], tab->fdout);
		child_procs_part_3(path, argv_value);
	}
	else
	{
		close(tab->pipefd[i - 1][0]);
		close(tab->fdout);
		return (pid);
	}
	return (0);
}
