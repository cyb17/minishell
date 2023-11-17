/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:15:48 by yachen            #+#    #+#             */
/*   Updated: 2023/11/17 16:25:24 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	clear_process(t_process *process)
{
	t_tokens	*tokenslist;
	t_tokens	*tmp;

	tokenslist = process->list_tokens;
	tmp = NULL;
	if (process->section_cmd)
		free(process->section_cmd);
	while (tokenslist)
	{
		tmp = tokenslist->next;
		//if (tokenslist->value)
		//	free(tokenslist->value);
		free(tokenslist);
		tokenslist = tmp;
	}
	free(process);
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
	while (res->prcs)
	{
		tmp = res->prcs->next;
		clear_process(res->prcs);
		res->prcs = tmp;
	}
	if (res->blt)
		clear_builtins(res->blt);
	if (res->tab)
	{
		if (res->tab->pipefd)
			free_pipefd(res->tab->pipefd, res->tab->nb_pipe);
		if (res->tab->tab_pid)
			free(res->tab->tab_pid);
		free(res->tab);
	}
}
