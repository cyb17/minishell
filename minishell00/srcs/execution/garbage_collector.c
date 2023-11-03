/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:15:48 by yachen            #+#    #+#             */
/*   Updated: 2023/11/03 12:23:50 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_process(t_list *process)
{
	if (process->section_cmd != NULL)
		free_tab(section_cmd);
	if (list_tokens != NULL)
		clear_lst(&list_tokens);
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