/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_procs_step_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:08:45 by yachen            #+#    #+#             */
/*   Updated: 2023/11/10 14:30:42 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

char	*child_procs_part_1(t_tab *tab, char **env, char *argv_value)
{
	char	*path;
	char	*env_exev[2];

	env_exev[0] = "PATH=/mnt/nfs/homes/yachen/bin:/usr/local/sbin:\
	/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	env_exev[1] = NULL;
	path = parsing_cmd(env, argv_value, env_exev);
	if (!path)
	{
		close_pipefd(tab->pipefd, tab->nb_pipe, tab->nb_pipe);
		garbage_collector(&tab->process, tab, tab->builtins, tab->input)
		free(argv_value);
		exit (1);
	}
	return (path);
}

void	child_procs_part_2(t_tab *tab, int input, int output, char *arg)
{
	if (dup2(input, STDIN_FILENO) < 0 || dup2(output, STDOUT_FILENO) < 0)
	{
		close_pipefd(tab->pipefd, tab->nb_pipe, tab->nb_pipe);
		garbage_collector(&tab->process, tab, tab->builtins, tab->input)
		free(arg);
		exit (1);
	}
	close_allfd(tab);
}

void	child_procs_part_3(t_tab *tab, char *path, char *argv_value)
{
	char	**cmd;

	cmd = make_cmd(argv_value);
	if (execve(path, cmd, NULL) == -1)
	{
		perror("Error: execve");
		close_pipefd(tab->pipefd, tab->nb_pipe, tab->nb_pipe);
		garbage_collector(&tab->process, tab, tab->builtins, tab->input)
		free(path);
		free(argv_value);
		exit (1);
	}
}
