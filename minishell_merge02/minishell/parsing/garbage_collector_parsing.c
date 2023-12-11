/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_parsing.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:15:48 by yachen            #+#    #+#             */
/*   Updated: 2023/12/11 17:24:05 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	clear_tokens_list(t_tokens *list)
{
	t_tokens	*tmp;

	tmp = NULL;
	while (list)
	{
		tmp = list;
		list = (list)->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	clear_process_list(t_process *process)
{
	t_process	*tmp;

	tmp = NULL;
	if (process == NULL)
		return ;
	while (process)
	{
		tmp = process;
		if (tmp->section_cmd)
			free(tmp->section_cmd);
		tmp->section_cmd = NULL;
		if (tmp->list_tokens)
			clear_tokens_list(tmp->list_tokens);
		tmp->list_tokens = NULL;
		if (process->next != NULL)
		{
			process = (process)->next;
			free(tmp);
		}
		else
		{
			free(tmp);
			break ;
		}
	}
}

void	clean_pars(t_p *p)
{
	if (p->s != NULL)
		free(p->s);
	p->s = NULL;
	if (p->s0)
		free(p->s0);
	p->s0 = NULL;
	if (p->s1)
		free(p->s1);
	p->s1 = NULL;
	p->s3 = NULL;
	if (p->words != NULL)
		free_tab(p->words);
	p->words = NULL;
	if (p->tkn)
		free_tab(p->tkn);
	p->tkn = NULL;
	p->all = NULL;
	if (p)
		free(p);
}

void	clean_loop(t_all *all)
{
	clean_pars(all->p);
	clear_process_list(all->process);
}

bool	ft_error(char *s, t_all *all, int code)
{
	g_signal[0] = code;
	printf("%s", s);
	clean_loop(all);
	return (false);
}