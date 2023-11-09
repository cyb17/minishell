/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:15:48 by yachen            #+#    #+#             */
/*   Updated: 2023/11/09 16:54:31 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_process(t_process *process)
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

void	garbage_collector(t_process **proces, t_tab *tab, t_builtins *builtins)
{
	t_process	*tmp;

	tmp = NULL;
	while (proces != NULL)
	{
		tmp = (*proces)->next;
		clear_process(*proces);
		*proces = tmp;
	}
	free_pipefd(tab->pipefd);
	free(tab->tab_pid);
	clear_lst(builtins->envlist);
	clear_lst(builtins->explist);
	free_tab(arg);
}
