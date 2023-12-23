/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:15:48 by yachen            #+#    #+#             */
/*   Updated: 2023/12/14 16:05:16 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

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
		if (tmp->heredoc)
		{
			if (unlink(tmp->heredoc) == -1)
				perror("Error: clear_prcs_list: unlink");
			free(tmp->heredoc);
		}
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

void	garbage_collector_child(t_res *res)
{
	if (res->prcs)
	{
		clear_prcs_list(&res->prcs);
		res->prcs = NULL;
	}
	if (res->blt)
	{
		clear_builtins(res->blt);
		res->blt = NULL;
	}
	if (res->tab)
	{
		if (res->tab->pipefd)
			free_pipefd(res->tab->pipefd, res->tab->nb_pipe);
		free(res->tab);
		res->tab = NULL;
	}
}

void	garbage_collector_parent(t_res *res)
{
	if (res->prcs)
	{
		clear_prcs_list(&res->prcs);
		res->prcs = NULL;
	}
	if (res->tab)
	{
		if (res->tab->pipefd)
			free_pipefd(res->tab->pipefd, res->tab->nb_pipe);
		free(res->tab);
		res->tab = NULL;
	}
}
