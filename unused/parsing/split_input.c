/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:58:07 by nap               #+#    #+#             */
/*   Updated: 2023/12/17 14:58:24 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_process	*create_process(t_p *p, int end)
{
	t_process	*process;

	process = (t_process *)malloc(sizeof(t_process));
	if (!process)
	{
		ft_error(ERROR_M4, p->all, 1);
		return (NULL);
	}
	process_init(process);
	process->section_cmd = ft_strdup_part(p->s1, p->start, end);
	if (!process->section_cmd)
	{
		ft_error(ERROR_M4, p->all, 1);
		return (NULL);
	}
	process->section_cmd_id = p->id;
	return (process);
}

bool	map_list(t_p *p, t_process **list_process, t_process *new, int i)
{
	new = create_process(p, i);
	if (!new)
		return (ft_error(ERROR_M8, p->all, 1));
	ft_procsadd_back(list_process, new);
	return (true);
}

void	make_process_list(t_p *p, t_process **list_process)
{
	t_process	*new;
	int			i;

	new = NULL;
	i = 0;
	while (p->s1[i] && i <= (int)ft_strlen(p->s1))
	{
		if (p->s1[i] == '|')
		{
			if (b_q(p->s1, i) == i)
			{
				map_list(p, list_process, new, i);
				p->start = i + 1;
			}
			p->id++;
		}
		i++;
	}
	if (p->id == 1)
		map_list(p, list_process, new, (int)ft_strlen(p->s1));
	else
		map_list(p, list_process, new, (int)ft_strlen(p->s1));
}

t_tokens	*create_tokens(char *str, int id, t_p *p)
{
	t_tokens	*tokens;

	tokens = (t_tokens *)malloc(sizeof(t_tokens));
	if (!tokens)
	{
		ft_error(ERROR_M5, p->all, 1);
		return (NULL);
	}
	token_init(tokens);
	tokens->value = ft_strdup(str);
	tokens->id = id;
	if (str)
		free(str);
	return (tokens);
}

bool	make_token_list(t_process *process, t_list *envlist, t_p *p)
{
	t_tokens	*new_token;
	int			i;
	char		*tkn_word;

	new_token = NULL;
	while (process != NULL)
	{
		p->id = 0;
		i = 0;
		if (manage_tkn(process, p) == false)
			return (false);
		while (p->tkn[i] != NULL)
		{
			tkn_word = clean_word(p->tkn[i], p, &envlist);
			if (tkn_word != NULL)
			{
				p->id++;
				new_token = create_tokens(tkn_word, p->id, p);
				if (!new_token)
					return (ft_error(ERROR_M5, p->all, 1));
				ft_tokenadd_back(&process->list_tokens, new_token);
			}
			i++;
		}
		process = process->next;
	}
	return (true);
}
