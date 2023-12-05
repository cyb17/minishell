/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:15:48 by yachen            #+#    #+#             */
/*   Updated: 2023/12/05 12:54:28 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

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

static void	clear_tk_list(t_tokens **list)
{
	t_tokens	*tmp;

	tmp = NULL;
	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

static void	clear_prcs_list(t_process **process)
{
	t_process	*tmp;

	tmp = NULL;
	while (*process)
	{
		tmp = *process;
		*process = (*process)->next;
		if (tmp->section_cmd)
			free(tmp->section_cmd);
		if (tmp->list_tokens)
			clear_tk_list(&tmp->list_tokens);
		free(tmp);
	}
}

static void	clear_builtins(t_builtins *blt)
{
	if (blt->envlist)
		clear_lst(&blt->envlist);
	if (blt->explist)
		clear_lst(&blt->explist);
	free_tab(blt->arg);
	blt->arg = NULL;
	free(blt);
	blt = NULL;
}

void	garbage_collector(t_res *res)
{
	t_process	*tmp;

	tmp = NULL;
	if (res->prcs)
		clear_prcs_list(&res->prcs);
	if (res->blt)
		clear_builtins(res->blt);
	if (res->tab)
	{
		if (res->tab->pipefd)
			free_pipefd(res->tab->pipefd, res->tab->nb_pipe);
		free(res->tab);
	}
}
