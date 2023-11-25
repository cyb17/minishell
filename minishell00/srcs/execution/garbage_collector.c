/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:15:48 by yachen            #+#    #+#             */
/*   Updated: 2023/11/25 18:12:28 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	clear_tokens_list(t_tokens **list)
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

static void	clear_process_list(t_process **process)
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
			clear_tokens_list(&tmp->list_tokens);
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
	free(blt);
}

void	garbage_collector(t_res *res)
{
	t_process	*tmp;

	tmp = NULL;
	if (res->input)
		free(res->input);
	clear_process_list(&res->prcs);
	if (res->blt)
		clear_builtins(res->blt);
	if (res->tab)
	{
		if (res->tab->pipefd)
			free_pipefd(res->tab->pipefd, res->tab->nb_pipe);
		free(res->tab);
	}
}
