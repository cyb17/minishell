/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:15:48 by yachen            #+#    #+#             */
/*   Updated: 2023/11/08 16:22:16 by yachen           ###   ########.fr       */
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

void	garbage_collector(t_process **process_list)
{
	t_process	*tmp;

	tmp = NULL;
	while (process_list != NULL)
	{
		tmp = (*process_list)->next;
		clear_process(*process_list);
		*process_list = tmp;	
	}
}
