/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:57:17 by yachen            #+#    #+#             */
/*   Updated: 2023/11/16 11:02:53 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_compare(char *limiter, char *str)
{
	int	i;

	i = 0;
	while (limiter[i])
	{
		if (limiter[i] != str[i])
			return (0);
		i++;
	}
	if (limiter[i] == '\0' && str[i] == '\n')
		return (1);
	return (0);
}

void	close_allfd(t_tab *tab)
{
	int	i;

	i = 0;
	close(tab->fdin);
	close(tab->fdout);
	while (i < tab->nb_pipe)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
}

void	wait_proces(int *pid, int nb_proces)
{
	int	i;
	int	status;

	i = 0;
	while (i < nb_proces)
	{
		if (pid[i] != 0)
			waitpid(pid[i], &status, 0);
		i++;
	}
}

void	ft_error(char *where, char *what)
{
	char	*tmp;
	char	*err;

	tmp = ft_strjoin(where, what);
	if (!tmp)
	{
		ft_putstr_fd(where, 2);
		ft_putstr_fd(what, 2);
		ft_putchar_fd('\n', 2);
		return ;
	}
	err = ft_strjoin(tmp, "\n");
	if (!err)
	{
		free(tmp);
		ft_putstr_fd(where, 2);
		ft_putstr_fd(what, 2);
		ft_putchar_fd('\n', 2);
		return ;
	}
	free(tmp);
	ft_putstr_fd(err, 2);
	free(err);
}

/*
int main(void)
{
	ft_error("Error: echo: ", strerror(errno));
}*/
