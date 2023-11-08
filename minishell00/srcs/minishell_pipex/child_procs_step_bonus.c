/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_procs_step_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:08:45 by yachen            #+#    #+#             */
/*   Updated: 2023/11/08 10:27:34 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

char	*child_procs_part_1(int i, t_tab *tab, char **env, char *argv_value)
{
	char	*path;
	char	*env_exev[2];

	env_exev[0] = "PATH=/mnt/nfs/homes/yachen/bin:/usr/local/sbin:\
	/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	env_exev[1] = NULL;
	path = parsing_cmd(env, argv_value, env_exev);
	if (!path)
	{
		clean_all(tab, i, 1);
		exit(EXIT_FAILURE);
	}
	return (path);
}

void	child_procs_part_2(int i, t_tab *tab, int input, int output)
{
	if (dup2(input, STDIN_FILENO) < 0 || dup2(output, STDOUT_FILENO) < 0)
	{
		clean_all(tab, i, 1);
		ft_perror("dup2", 1);
	}
	clean_all(tab, i, 0);
}

void	child_procs_part_3(char *path, char *argv_value)
{
	char	**cmd;

	cmd = make_cmd(argv_value);
	if (execve(path, cmd, NULL) == -1)
		ft_perror("execve", 1);
}
