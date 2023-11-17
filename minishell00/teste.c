#include <stdio.h>
#include <stdlib.h>
#include "srcs/libft/libft.h"
#include <errno.h>
#include <string.h>

void	free_pipefd(int **pipefd, int nb_pipe)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
		free(pipefd[i++]);
	free(pipefd);
}

int	pipe_pipefd(int **pipefd, int nb_pipe)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
	{
		if ((pipe(pipefd[i])) < 0)
		{
			perror("fill_tab: creat_pipefd");
			while (--i >= 0)
			{
				close(pipefd[i][0]);
				close(pipefd[i][1]);
			}
			free_pipefd(pipefd);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	creat_pipefd(t_tab *tab)
{
	int	i;

	i = 0;
	tab->pipefd = (int **)malloc(sizeof(int *) * (tab->nb_pipe));
	if (!(tab->pipefd))
	{
		ft_putstr_fd("fill_tab: malloc_pipefd: pipefd: malloc failed\n", 2);
		return (-1);
	}
	i = 0;
	while (i < tab->nb_pipe)
	{
		tab->pipefd[i] = (int *)malloc(sizeof(int) * 2);
		if (!(tab->pipefd[i]))
		{
			ft_putstr_fd("fill_tab: malloc_pipefd: []: malloc failed\n", 2);
			free_pipefd(tab->pipefd, i);
			return (-1)
		}
		i++;
	}
	if (pipe_pipefd(tab->pipefd, tab->nb_pipe) == -1)
		return (-1);
	return (0);
}

t_tab	*fill_tab(t_process *process, t_builtins *blt, char *input)
{
	t_tab	*tab

	tab = (t_tab *)malloc(sizeof(tab));
	if (!tab)
		return (NULL);
	tab->fdin = 0;
	tab->fdout = 0;
	tab->nb_pipe = find_nb_process(process) - 1;
	tab->tab_pid = (pit_t *)malloc(sizeof(pid_t) * nb_pipe + 1);
	if (!tab->tab_pid)
	{
		free(tab);
		ft_putstr_fd("fill_tab: tab_pid: malloc failed\n", 2);
		return (NULL);
	}
	ft_memset(tab->tab_pid, 0, tab->nb_pipe + 1);
	if (creat_pipefd(tab) == -1)
	{
		free(tab->tab_pid);
		free(tab);
		return (NULL);
	}
	return (tab);
}

int	main(int argc, char **argv, char **env)
{
	t_tab	*tab;

	(void)argc;
	(void)argv;
	tab = fill_tab(env);
	if (!blt)
		printf("malloc failed\n");
	else
		print_explist(blt->explist);
	print_explist(blt->envlist);
	clear_lst(&blt->explist);
	clear_lst(&blt->envlist);
	free(blt);
}