/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:22:59 by achevala          #+#    #+#             */
/*   Updated: 2023/12/09 14:31:26 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	nb_words(char *s, char c)
{
	int		m;
	char	*s0;
	int		i;

	m = 0;
	s0 = s;
	i = 0;
	while (*s0 && *s0 != '\0')
	{
		while (b_q(s, i) == i && *s0)
			m = (nb_words_end(s, &i, &s0, c) + m);
		while (b_q(s, i) > i)
		{
			while (*s0 != '\0')
			{
				if (b_q(s, i) == i)
					break ;
				s0++;
				i++;
			}
		}
	}
	return (m);
}

int	size_words(char *s, char c)
{
	int		l;
	char	*s1;

	l = 0;
	s1 = s;
	while (*s1 != c && *s1 != '\0')
	{
		while (*s1 != '\0' && (*s1 == '\'' || *s1 == '"'))
			size_word_end(s, &l, &s1, c);
		while (*s1 != '\0' && *s1 != c && b_q(s, l) == l
			&& (*s1 != '\'' && *s1 != '"'))
		{
			l++;
			s1++;
		}
	}
	return (l);
}

void	freetab(char **tab)
{
	int	i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

char	**write_in(char **tab, char *s, char c, t_p *p)
{
	char	*s2;
	int		max;

	s2 = s;
	max = nb_words(s, c);
	while (*s2 && *s2 != '\0' && p->i <= max)
	{
		if (*s2 && *s2 != '\0' && (p->k > 0) && s[p->k - 1] == c)
			p->j = 0;
		while (*s2 != '\0' && *s2 != c && (*s2 == '\'' || *s2 == '"'))
		{
			tab[p->i][p->j] = *s2;
			s2++;
			p->k++;
			p->j++;
			first_loop(p, &tab, &s2, s);
		}
		second_loop(p, &tab, &s2, s);
	}
	if (p->i != max)
		tab[p->i][p->j] = '\0';
	tab[max] = NULL;
	return (tab);
}

char	**ft_split_minishell(char *s, char c, t_p *p)
{
	char		**tab;
	char		*s3;

	p->l = 0;
	p->z = 0;
	s3 = s;
	tab = malloc(sizeof(char *) * (nb_words(s, c) + 1));
	if (!tab || s == 0)
	{
		ft_putstr_fd(" ft_split_minishell : malloc failed", 2);
		return (NULL);
	}
	while (*s3)
		split_mini_loop(&tab, p, &s3, s);
	p->i = 0;
	p->j = 0;
	p->k = 0;
	return (write_in(tab, s, c, p));
}
