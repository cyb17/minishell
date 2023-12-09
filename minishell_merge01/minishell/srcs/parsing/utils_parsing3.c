/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:16:43 by achevala          #+#    #+#             */
/*   Updated: 2023/12/09 14:31:26 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

char	*manage_words_p1(t_p *p, t_list **envlist)
{
	char	*cpy;

	cpy = NULL;
	p->i++;
	while (p->i < (p->len1 - 1))
	{
		if (p->s3[p->i] != '$')
		{
			cpy = cpychar(p->s3, p->i, cpy);
			p->i++;
		}
		if (p->s3[p->i] == '$')
			cpy = manage_expand(p, envlist, cpy);
	}
	return (cpy);
}

char	*manage_expand(t_p *p, t_list **envlist, char *cpy)
{
	char	*tmp;

	tmp = expand_value(p->s3, p->i, envlist);
	p->i++;
	if (tmp != NULL)
	{
		p->cpy2 = cpy;
		cpy = my_strjoin(p->cpy2, tmp);
		if (p->cpy2)
			free(p->cpy2);
		p->i++;
	}
	if (is_exp_char(p->s3[p->i]) == true)
	{
		while (is_exp_char(p->s3[p->i]) == true)
			p->i++;
	}
	else if (p->s3[p->i] == '?' || p->s3[p->i] == '$')
	{
		while (p->s3[p->i] == '?' || p->s3[p->i] == '$')
			p->i++;
	}
	return (cpy);
}

char	*manage_words_p2(t_p *p)
{
	char	*cpy;

	cpy = NULL;
	p->i++;
	while (p->i < (p->len1 - 1))
	{
		cpy = cpychar(p->s3, p->i, cpy);
		p->i++;
	}
	return (cpy);
}

char	*manage_words_p3(t_p *p, t_list **envlist)
{
	char	*cpy;
	char	*cpy2;

	cpy = NULL;
	cpy2 = NULL;
	while (p->i < p->len1)
	{
		if (p->s3[p->i] == '$')
			cpy = manage_expand(p, envlist, cpy);
		if (cpy == NULL && p->i < p->len1)
			cpy = ft_strdup_section(p->s3, p->i, p->i + 1);
		else if (p->i < p->len1)
			cpy = manage_words_p4(p, cpy);
		p->i++;
	}
	if (cpy != NULL)
	{
		cpy2 = deepclean(cpy);
		free(cpy);
		return (cpy2);
	}
	return (cpy2);
}

char	*manage_words_p4(t_p *p, char *cpy)
{
	char	*tmp;
	char	*cpy2;

	tmp = ft_strdup_section(p->s3, p->i, p->i + 1);
	cpy2 = cpy;
	cpy = my_strjoin(cpy2, tmp);
	if (cpy2)
		free(cpy2);
	if (tmp != NULL)
		free(tmp);
	return (cpy);
}
