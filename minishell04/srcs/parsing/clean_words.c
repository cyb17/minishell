/* ************************************************************************** */
/*	                                                                          */
/*                                                        :::      ::::::::   */
/*   clean_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:02:21 by achevala          #+#    #+#             */
/*   Updated: 2023/11/11 21:00:45 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

char	*delete_quotes(char *s)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = NULL;
	while (*s && s[i] != '\0' && i <= ((int)ft_strlen(s)))
	{
		if (s[i] && s [i + 1] && (s[i] == '\'' && s[i + 1] == '\'')
			&& b_q(s, i) == i)
			i = i + 2;
		else if (s[i] && s [i + 1] && (s[i] == '"' && s[i + 1] == '"'
				&& b_q(s, i) == i))
			i = i + 2;
		else if (s[i] != '\0')
		{
			if (cpy == NULL)
				cpy = ft_strdup_part(s, i, i + 1);
			else
				cpy = cpychar(s, i, cpy);
			i++;
		}
	}
	if (cpy == NULL)
		cpy = ft_strdup("' '");
	return (cpy);
}

char	*cpychar(char *s, int i, char *cpy)
{
	char	*cpy2;
	char	*tmp;

	if (cpy == NULL)
		cpy = ft_strdup_part(s, i, i + 1);
	else
	{
		tmp = ft_strdup_part(s, i, i + 1);
		cpy2 = cpy;
		cpy = my_strjoin(cpy2, tmp);
		if (cpy2)
			free(cpy2);
		if (tmp != NULL)
			free(tmp);
	}
	return (cpy);
}

void	deep_clean_in(char *s, int *i, char **cpy)
{
	(*cpy) = cpychar(s, *i, *cpy);
	(*i)++;
}

char	*deepclean(char *s)
{
	char	*cpy;
	int		j;
	int		i;

	j = 0;
	i = 0;
	cpy = NULL;
	while (*s && s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			if (check_quotes(s, s[i], i) > i)
			{
				j = check_quotes(s, s[i], i);
				i++;
				while (i < j)
					deep_clean_in(s, &i, &cpy);
			}
		}
		else
			cpy = cpychar(s, i, cpy);
		i++;
	}
	return (cpy);
}

char	*clean_word(char *s, t_p *p, t_list **envlist)
{
	char	*cpy;

	if (s)
		p->len1 = ft_strlen(s);
	p->s3 = s;
	p->i = 0;
	cpy = NULL;
	if (p->s3 && (p->s3[p->i] == '"' && p->s3[p->len1 - 1] == '"')
		&& (check_quotes(p->s3, p->s3[p->i], p->i) == (p->len1 - 1)))
		return (manage_words_p1(p, envlist));
	if (p->s3 && (p->s3[p->i] == '\'' && p->s3[p->len1 - 1] == '\'')
		&& (check_quotes(p->s3, p->s3[p->i], p->i) == (p->len1 - 1)))
		return (manage_words_p2(p));
	if (p->s3)
		cpy = manage_words_p3(p, envlist);
	return (cpy);
}
