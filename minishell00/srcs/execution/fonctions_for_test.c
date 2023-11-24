/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions_for_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:57:49 by yachen            #+#    #+#             */
/*   Updated: 2023/11/24 16:28:57 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_lst(t_list **list)
{
	t_list	*current;

	current = NULL;
	while (*list)
	{
		current = *list;
		*list = (*list)->next;
		free(current);
	}
}

t_list	*env_to_envlist(char **env)
{
	int		i;
	t_list	*envlist;
	t_list	*tmp;

	i = 0;
	envlist = NULL;
	while (env[i])
	{
		tmp = ft_lstnew(env[i]);
		if (!tmp)
		{
			clear_lst(&envlist);
			return (NULL);
		}
		ft_lstadd_back(&envlist, tmp);
		i++;
	}
	return (envlist);
}

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

// Close fdin, fdout 
// Close pipefd until nb_pipe
void	close_unsusedfd(t_tab *tab, int j)
{
	int	i;

	i = 0;
	//close(tab->fdin);
	//close(tab->fdout);
	while (i <= j && i < tab->nb_pipe)
	{
		close(tab->pipefd[i][0]);
		close(tab->pipefd[i][1]);
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

int	isnot_builtins(char *str)
{
	printf("str = %s\n", str);
	if ((ft_strcmp("echo", str) == 1) || (ft_strcmp("cd", str) == 1)
		|| (ft_strcmp("env", str) == 1) || (ft_strcmp("exit", str) == 1)
		|| (ft_strcmp("export", str) == 1) || (ft_strcmp("unset", str) == 1)
		|| (ft_strcmp("pwd", str) == 1))
		return (0);
	return (1);
}