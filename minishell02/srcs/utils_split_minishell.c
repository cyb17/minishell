/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split_minishell.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nap <nap@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:27:06 by achevala          #+#    #+#             */
/*   Updated: 2023/12/09 10:32:55 by nap              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	nb_words_end(char *s, int *i, char **s0, char c)
{
	int	m;

	m = 0;
	while (*(*s0) == c && *(*s0) != '\0')
	{
		if (b_q(s, (*i)) > (*i))
			break ;
		(*s0)++;
		(*i)++;
	}
	if (*(*s0) != c && *(*s0) != '\0'
		&& (b_q(s, (*i) - 1) == (*i) - 1))
		m++;
	while (*(*s0) != '\0' && *(*s0) != c)
	{
		if (b_q(s, (*i)) > (*i))
			break ;
		(*s0)++;
		(*i)++;
	}
	return (m);
}

void	size_word_end(char *s, int *l, char **s1, char c)
{
	(*s1)++;
	(*l)++;
	if (b_q(s, (*l)) > (*l) && *(*s1) != '\0')
	{
		while (b_q(s, (*l)) > (*l) && *(*s1) != '\0')
		{
			(*l)++;
			(*s1)++;
			if (b_q(s, (*l)) == (*l)
				&& b_q(s, (*l) - 1) > (*l) - 1)
			{
				(*s1)++;
				(*l)++;
			}
		}
	}
	while (*(*s1) != '\0' && *(*s1) != c && b_q(s, (*l)) == (*l)
		&& (*(*s1) != '\'' && *(*s1) != '"'))
	{
		(*l)++;
		(*s1)++;
	}
}

//checker les return
bool split_mini_loop(char ***tab, t_p *p, char **s3, char *s)
{
	
	while (*(*s3) == ' ' && *(*s3) != '\0' && b_q(s, p->l) == p->l)
	{
		(*s3)++;
		p->l++;
	}
	if (*(*s3) != ' ' && *(*s3) != '\0')
	{
		(*tab)[p->z] = malloc(sizeof(char) * (size_words((*s3), ' ') + 1));
		if (!(*tab)[p->z])
			return (ft_error(ERROR_MSG, p->all, 1));
		p->z++;
	}
	while (*(*s3) != ' ' && *(*s3) != '\0')
	{	
		end_split_mini(s3, s, p);
		while (*(*s3) && *(*s3) != '\0' && *(*s3) != ' ' && b_q(s, p->l) == p->l
			&& (*(*s3) != '\'' && *(*s3) != '"'))
		{
			p->l++;
			(*s3)++;
		}
	}
	return (true);
}

void end_split_mini(char **s3, char *s, t_p *p)
{
	while (*(*s3) && *(*s3) != '\0' && (*(*s3) == '\'' || *(*s3) == '"'))
	{
		(*s3)++;
		p->l++;
		if (b_q(s, p->l) > p->l && *(*s3) != '\0')
		{
			while (b_q(s, p->l) > p->l && *(*s3) != '\0')
			{
				p->l++;
				(*s3)++;
				if (b_q(s, p->l) == p->l
					&& b_q(s, p->l - 1) > p->l - 1)
				{
					(*s3)++;
					p->l++;
				}
			}
		}				
		while (*(*s3) != '\0' && *(*s3) != ' ' && b_q(s, p->l) == p->l
			&& (*(*s3) != '\'' && *(*s3) != '"'))
		{
			p->l++;
			(*s3)++;
		}
	}
}