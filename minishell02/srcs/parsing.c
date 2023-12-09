/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nap <nap@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:12:48 by nap               #+#    #+#             */
/*   Updated: 2023/12/09 10:31:02 by nap              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

bool	first_readind(char *input, t_all *all)
{
	int	i;
	int	j;

	i = 0;
	while (input[i] && i <= (int)ft_strlen(input))
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			j = check_quotes(input, input[i], i);
			if (i == j)
				return (ft_error(ERROR_QUOTES, all, 2));
			else
				i = j;
		}
		i++;
	}
	return (true);
}

bool	check_process(char *s, t_all *all)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] && s[i + 1] && s[i] == '|' && s[i + 1] == '|')
		return (ft_error(ERROR_PROCESS2, all, 2));
	if (s[i] == '|')
		return (ft_error(ERROR_PROCESS, all, 2));
	while (s[i])
	{
		if (my_strnstr(s + i, "|||", 3) == true && b_q(s, i) == i)
			return (ft_error(ERROR_PROCESS, all, 2));
		i++;
	}
	i--;
	if (s[i] == '|')
		return (ft_error(ERROR_PROCESS, all, 2));
	while (s[i] == ' ')
		i--;
	if (s[i] == '|')
		return (ft_error(ERROR_PROCESS, all, 2));
	return (true);
}


bool	check_redir(char *s, t_all *all)
{
	int		i;
	bool	flag;

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
		if (redir_err1(s, all, i) == false)
			return(false);
		if (redir_err2(s, all, i, &flag) == false)
			return(false);
		else if (redir_err3(s, all, &i, &flag) == false)
			return (false);
		i++;
	}
	return (true);
}

int	ft_parse(char *line, t_all *all)
{
	t_list		*envlist;

	all->process = NULL;
	envlist = all->envlist;
	all->p = malloc(sizeof(t_p));
	if (!all->p)
	{
		ft_error(ERROR_M1, all, 1);
		return (-1);
	}
	pars_init(all->p, line, all);
	free(line);
	if (first_readind(all->p->s, all) == false)
		return (-1);
	all->p->s0 = delete_quotes(all->p->s);
	printf(" S0 : %s\n", all->p->s0);
	if (!all->p->s0)
	{
		ft_error(ERROR_M2, all, 1);
		return (-1);
	}
	all->p->s1 = add_space(all->p->s0);
	if (!all->p->s1)
	{
		ft_error(ERROR_M3, all, 1);
		return (-1);
	}
	printf(" S1 : %s\n", all->p->s1);
	if (check_redir(all->p->s1, all) == false)
		return (-1);
	if (check_process(all->p->s1, all) == false)
		return (-1);
	make_process_list(all->p, &all->process);
	if (!all->process)
	{
		ft_error(ERROR_M8, all, 1);
		return (-1);
	}
	if (make_token_list(all->process, envlist, all->p) == false)
		return (-1);
	if (!all->process->list_tokens)
	{
		ft_error(ERROR_M7, all, 1);
		return (-1);
	}
	ft_token(all->process);
	/* while ((*process))
		{
			printf("Contenu de section_cmd : %s\n", (*process)->section_cmd);
			(*process) = (*process)->next ;
		} */
	return (0);
}
