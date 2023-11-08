/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:39:32 by yachen            #+#    #+#             */
/*   Updated: 2023/11/08 10:27:47 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

static void	sub_main(t_tab *tab)
{
	free_tab_int(tab);
	if (access("/tmp/here_doc", F_OK) == 0)
	{
		if (unlink("/tmp/here_doc") == -1)
			ft_perror("unlink", 1);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_tab	tab;
	int		i;

	if (argc < 5)
		ft_perror("The number of parameters is not valid\n", 0);
	open_fd_bonus(&tab, &argv, argv[argc - 1], &argc);
	ft_init_tab(&tab, argc);
	i = 0;
	argv = argv + 2;
	while (i < argc - 3)
	{
		if (creat_pipefd(i, argc, tab.pipefd) == -1)
			break ;
		if (i == 0)
			tab.pid[i] = procs_fdin(i, &tab, env, *argv++);
		else if (i > 0 && i < argc - 4)
			tab.pid[i] = procs_pipe(i, &tab, env, *argv++);
		else
			tab.pid[i] = procs_fdout(i, &tab, env, *argv++);
		i++;
	}
	wait_proces(i, tab.pid, argc - 3);
	sub_main(&tab);
	return (0);
}
