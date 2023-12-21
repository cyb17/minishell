/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 18:58:13 by nap               #+#    #+#             */
/*   Updated: 2023/12/21 21:05:19 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	process_init(t_process *process)
{
	process->section_cmd = NULL;
	process->section_cmd_id = -1;
	process->list_tokens = NULL;
	process->pid = -1;
	process->next = NULL;
	process->heredoc = NULL;
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
	p->n = 0;
	p->tkn_word = NULL;
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

void	init_in_write_in(t_p *p)
{
	p->i = 0;
	p->j = 0;
	p->k = 0;
}

bool	is_only_space(char *s, t_all *all)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\0')
	{
		if (s[i] != ' ')
			return (true);
		i++;
	}
	clean_pars(all->p);
	return (false);
}
