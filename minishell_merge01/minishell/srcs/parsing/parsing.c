/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:12:48 by nap               #+#    #+#             */
/*   Updated: 2023/11/29 14:39:31 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

bool	first_readind(char *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i] && i <= (int)my_strlen(input))
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			j = check_quotes(input, input[i], i);
			if (i == j)
				return (false);
			else
				i = j;
		}
		i++;
	}
	return (true);
}
bool check_redir(char *s)
{
	int	i;
	bool flag;

	i = 0;
	flag = false;
	while (*s && s[i] != '\0')
	{
		while (s[i] == ' ')
			i++;
		while (*s && s[i] != '\0' && s[i + 1] != '\0' && s[i] != '<'
				&& s[i] != '>')
		{
			flag = false;
			i++;
		}
		if (between_quotes(s, i) == i && s[i] != '\0' && s[i + 1] != '\0'
			&& ((s[i] == '<' && s[i + 1] == '>')
			|| (s[i] == '>' && s[i + 1] == '<')))
			return (false);
		if (s[i] != '\0' && s[i + 1] != '\0' && s[i + 2] != '\0'
			&& (s[i] == '<' || s[i] == '>') && (s[i + 1] == '<' 
			|| s[i + 1] == '>') && (s[i + 2] == '<' || s[i + 2] == '>')
			&& between_quotes(s, i) == i)
			return (false);
		if (between_quotes(s, i) == i && s[i] != '\0' && s[i + 1] != '\0' 
			&&((s[i] == '<' && (s[i + 1] != '<')) || (s[i] == '>' 
			&& s[i + 1] != '>')))
			{
				if (flag == true)
					return (false);
				flag = true;
			}
		else if (between_quotes(s, i) == i && s[i] != '\0' && s[i + 1] != '\0' 
			&&((s[i] == '<' && (s[i + 1] == '<')) || (s[i] == '>' 
			&& s[i + 1] == '>')))
			{
				if (flag == true)
					return (false);
				flag = true;
				i++;
			}
		i++;
	}
	return (true);
}

// "" '$PWD  !' < | << $? >> cou'cou' | "$USER" $USE'R'



int	ft_parse(char *line, t_all *all)
{
	t_list		*envlist;
	
	all->process = NULL;
	envlist = all->envlist;
	all->p = malloc(sizeof(t_p));
	if (!all->p)
	{
		ft_putstr_fd("error: create_process: malloc failed\n", 2);
		return (1);
	}
	pars_init(all->p, line);
	if (first_readind(all->p->s) == false)
	{
		ft_putstr_fd("error: quotes\n", 2);
		return (1);
	}
	all->p->s0 = delete_quotes(all->p->s);
	free(line);
	all->p->s1 = add_space(all->p->s0);
	/* printf(" S1 : %s\n", all->p->s1); */
	all->p->s2 = input_max(all, envlist);
	if (!all->p->s2)
		return (1);
	/* printf(" S2: %s\n", all->p->s2); */
	if (check_redir(all->p->s1) == false)
	{
		ft_putstr_fd("error: redir\n", 2);
		return (1);
	}
	make_process_list(all->p, &all->process);
	make_token_list(all->process, envlist, all->p);
	ft_token(all->process);
	/* while ((*process))
		{
			printf("Contenu de section_cmd : %s\n", (*process)->section_cmd);
			(*process) = (*process)->next ;
		} */
	return (0);
}
