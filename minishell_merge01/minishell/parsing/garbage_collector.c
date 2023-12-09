/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:15:48 by yachen            #+#    #+#             */
/*   Updated: 2023/12/09 14:31:26 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

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
	list = NULL;
}

void	clear_process_list(t_process *process)
{
	t_process	*tmp;

	tmp = NULL;
	if (process == NULL)
		return;
	while (process)
	{
		tmp = process;
		if (tmp->section_cmd)
			free(tmp->section_cmd);
		tmp->section_cmd = NULL;
		if (tmp->cmds)
			free_tab(tmp->cmds);
		tmp->cmds = NULL;
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
			break;
		}
	}
	process = NULL;
}


void clean_pars(t_p *p)
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
	if (p->s2)
		free(p->s2);
	p->s2 = NULL;
	if (p->words)
		free_tab(p->words);
	p->words = NULL;
	if (p->tkn)
		free_tab(p->tkn);
	p->tkn = NULL;
}

void	clean_loop(t_all *all)
{
	clean_pars(all->p);
	clear_process_list(all->process);
}

/* static void	clear_builtins(t_builtins *blt)
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
		if (res->tab->fdin > 2)
			close(res->tab->fdin);
		if (res->tab->fdout > 2)
			close(res->tab->fdout);
		if (res->tab->pipefd)
			free_pipefd(res->tab->pipefd, res->tab->nb_pipe);
		if (res->tab->tab_pid)
			free(res->tab->tab_pid);
		free(res->tab);
	}
} */
