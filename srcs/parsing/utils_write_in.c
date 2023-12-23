/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_write_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:31:03 by achevala          #+#    #+#             */
/*   Updated: 2023/12/11 12:47:36 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	first_loop(t_p *p, char ***tab, char **s2, char *s)
{
	if (b_q(s, p->k) > p->k && *(*s2) != '\0')
	{
		while (b_q(s, p->k) > p->k && *(*s2) != '\0')
		{
			(*tab)[p->i][p->j] = *(*s2);
			(*s2)++;
			p->k++;
			p->j++;
			if (b_q(s, p->k) == p->k && b_q(s, p->k - 1) > p->k - 1)
			{
				(*tab)[p->i][p->j] = *(*s2);
				(*s2)++;
				p->k++;
				p->j++;
			}
		}
	}
	while (*(*s2) != '\0' && *(*s2) != ' ' && b_q(s, p->k) == p->k
		&& (*(*s2) != '\'' && *(*s2) != '"'))
	{
		(*tab)[p->i][p->j] = *(*s2);
		(*s2)++;
		p->k++;
		p->j++;
	}
}

void	second_loop(t_p *p, char ***tab, char **s2, char *s)
{
	while (*(*s2) != '\0' && *(*s2) != ' ' && b_q(s, p->k) == p->k
		&& (*(*s2) != '\'' && *(*s2) != '"'))
	{
		(*tab)[p->i][p->j] = *(*s2);
		(*s2)++;
		p->k++;
		p->j++;
	}
	if (*(*s2) != '\0' && *(*s2) == ' ' && p->j > 0)
	{
		(*tab)[p->i][p->j] = '\0';
		p->i++;
		while (b_q(s, p->k) == p->k && *(*s2) == ' '
			&& *(*s2) && *(*s2) != '\0')
		{
			(*s2)++;
			p->k++;
		}
	}
	if ((b_q(s, p->k) == p->k && *(*s2) == ' ' && *(*s2) && *(*s2) != '\0'))
	{
		(*s2)++;
		p->k++;
	}
}

int	my_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

bool	manage_tkn(t_process *process, t_p *p)
{
	if (p->tkn)
		freetab(p->tkn);
	p->tkn = ft_split_minishell(process->section_cmd, ' ', p);
	if (!p->tkn)
		return (ft_error(ERROR_M6, p->all, 1));
	return (true);
}
