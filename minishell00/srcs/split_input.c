/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:58:07 by nap               #+#    #+#             */
/*   Updated: 2023/11/27 15:05:50 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

t_process	*create_process(t_p *p, int end)
{
	t_process	*process;

	process = (t_process *)malloc(sizeof(t_process));
	if (!process)
	{
		ft_putstr_fd("error: create_process: malloc failed", 2);
		return (NULL);
	}
	process_init(process);
	process->section_cmd = ft_strdup_section(p->s2, p->start, end);
	process->cmds = ft_split_minishell(process->section_cmd, ' ');
	process->section_cmd_id = p->id;
	return (process);
}

void	map_list(t_p *p, t_process **list_process, t_process *new, int i)
{
	new = create_process(p, i);
	ft_procsadd_back(list_process, new);
}

void	make_process_list(t_p *p, t_process **list_process)
{
	t_process	*new;
	int			i;

	new = NULL;
	i = 0;
	while (p->s2[i] && i <= (int)my_strlen(p->s2))
	{
		if (p->s2[i] == '|')
		{
			if (between_quotes(p->s2, i) == i)
			{
				map_list(p, list_process, new, i);
				p->start = i + 1;
			}
			p->id++;
		}
		i++;
	}
	if (p->id == 1)
		map_list(p, list_process, new, (int)my_strlen(p->s2));
	else
		map_list(p, list_process, new, (int)my_strlen(p->s2));
}

t_tokens	*create_tokens(char *str, int id)
{
	t_tokens	*tokens;

	tokens = (t_tokens *)malloc(sizeof(t_tokens));
	if (!tokens)
	{
		ft_putstr_fd("error: create_tokens: malloc failed", 2);
		return (NULL);
	}
	token_init(tokens);
	tokens->value = ft_strdup(str);
/* 	printf("token value = %s\n", tokens->value); */
	tokens->id = id;
	return (tokens);
}

void	make_token_list(t_process *process, t_list *envlist, t_p *p)
{
	t_tokens	*new_token;
	int			id;
	int			i;
	(void)envlist;

	new_token = NULL;
	while (process != NULL)
	{
		id = 0;
		i = 0;
		p->tkn = ft_split_minishell(process->section_cmd, ' ');
		while (p->tkn[i] != NULL)
		{
			id++;
			new_token = create_tokens(p->tkn[i], id);
			ft_tokenadd_back(&process->list_tokens, new_token);
			i++;
		}
		process = process->next;
	}
}

char *input_max(t_all *all, t_list *envlist)
{
	char 	*res;
	int		i;
	char 	*cleaned;
	char	*cpy;
	
	i = 0;
	res = NULL;
	all->p->words = ft_split_minishell(all->p->s1, ' ');
	while (all->p->words[i] != NULL)
	{
		cleaned = clean_word(all->p->words[i], &envlist);
		/* printf("cleaned %d: %s\n", i, cleaned); */
		if (res != NULL)
			res = add_blank(res);
		cpy = res;
		res = my_strjoin(cpy, cleaned);
		if (cpy)
			free(cpy);
		if (cleaned != NULL)
			free(cleaned);
		i++;
	}
	/* printf("RES: %s\n", res); */
	return (res);
}
