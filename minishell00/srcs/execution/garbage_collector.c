/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:15:48 by yachen            #+#    #+#             */
/*   Updated: 2023/11/10 14:39:50 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	clear_process(t_process *process)
{
	t_tokens	**tokenslist;
	t_tokens	*tmp;

	*tokenslist = process->list_tokens;
	tmp = NULL;
	free_tab(process->section_cmd);
	while (*tokenslist != NULL)
	{
		tmp = (*tokenslist)->next;
		if ((*tokenslist)->value != NULL)
			free((*tokenslist)->value);
		free(*tokenslist);
		*tokenslist = tmp;
	}
}

void	garbage_collector(t_process **pc, t_tab *tb, t_builtins *b, char *inpt)
{
	t_process	*tmp;

	tmp = NULL;
	while (pc)
	{
		tmp = (*pc)->next;
		clear_process(*pc);
		*pc = tmp;
	}
	if (b->envlist)
		clear_lst(b->envlist);
	if (b->explist)
		clear_lst(builtins->explist);
	free_tab(arg);
	if (inpt)
		free(inpt);
	if (tb->pipefd)
		free_pipefd(tb->pipefd);
	if (tb->tab_pid)
		free(tb->tb_pid);
}
