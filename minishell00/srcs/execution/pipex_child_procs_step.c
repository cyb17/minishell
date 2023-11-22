/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child_procs_step.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:08:45 by yachen            #+#    #+#             */
/*   Updated: 2023/11/22 13:54:41 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Check command and find command_path
char	*child_procs_part_1(t_res *res, char **env, char *argv_value)
{
	char	*path;
	char	*env_exev[2];

	env_exev[0] = "PATH=/mnt/nfs/homes/yachen/bin:/usr/local/sbin:\
	/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	env_exev[1] = NULL;
	path = parsing_cmd(env, argv_value, env_exev);
	if (!path)
	{
		garbage_collector(res);
		free(argv_value);
		exit (1);
	}
	return (path);
}

// Redirect stdin and stdout of child process
void	child_procs_part_2(t_res *res, int input, int output, char *arg, int i)
{
	if (dup2(input, STDIN_FILENO) < 0 || dup2(output, STDOUT_FILENO) < 0)
	{
		garbage_collector(res);
		free(arg);
		exit (1);
	}
	(void)i;
	// close_unsusedfd(res->tab, i);
}

// Execute the command
void	child_procs_part_3(t_res *res, char *path, char *argv_value)
{
	char	**cmd;

	cmd = make_cmd(argv_value);
	if (execve(path, cmd, NULL) == -1)
	{
		perror("Error: execve");
		garbage_collector(res);
		free(path);
		free(argv_value);
		exit (1);
	}
}
