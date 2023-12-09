/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 18:58:13 by nap               #+#    #+#             */
/*   Updated: 2023/12/06 18:17:49 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	process_init(t_process *process)
{
	process->section_cmd = NULL;
	process->section_cmd_id = -1;
	process->list_tokens = NULL;
	process->pid = -1;
	process->next = NULL;
}

int	pars_init(t_p *p, char *line, t_all *all)
{
	p->s = NULL;
	p->s = ft_strdup(line);
	if (!p->s)
	{
		ft_putstr_fd("error: pars_init: malloc failed", 2);
		return (1);
	}
	printf("INPUT : %s\n", p->s);
	p->s0 = NULL;
	p->s1 = NULL;
	p->cpy2 = NULL;
	p->s3 = NULL;
	p->len = ft_strlen(line);
	p->len1 = -1;
	p->start = 0;
	p->id = 1;
	p->i = 0;
	p->j = 0;
	p->k = 0;
	p->l = 0;
	p->words = NULL;
	p->tkn = NULL;
	p->all = all;
	return (0);
}

void	token_init(t_tokens *tokens)
{
	tokens->id = -1;
	tokens->type = -1;
	tokens->value = NULL;
	tokens->next = NULL;
}

void	all_init(t_all *all, char **env)
{
	all->process = NULL;
	all->envlist = NULL;
	all->envlist = env_to_envlist(env);
	all->process = NULL;
	all->p = NULL;
}

void	init_in_write_in(t_p *p)
{
	p->i = 0;
	p->j = 0;
	p->k = 0;
}
