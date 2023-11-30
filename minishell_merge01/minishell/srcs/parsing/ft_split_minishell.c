/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:22:59 by achevala          #+#    #+#             */
/*   Updated: 2023/11/28 13:32:36 by yachen           ###   ########.fr       */
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
		while (between_quotes(s, i) == i && *s0)
		{
			while (*s0 == c && *s0 != '\0')
			{
				if (between_quotes(s, i) > i)
					break ;
				s0++;
				i++;
			}
			if (*s0 != c && *s0 != '\0'
				&& (between_quotes(s, i - 1) == i - 1))
				m++;
			while (*s0 != '\0' && *s0 != c)
			{
				if (between_quotes(s, i) > i)
					break ;
				s0++;
				i++;
			}
		}
		while (between_quotes(s, i) > i)
		{
			while (*s0 != '\0')
			{
				if (between_quotes(s, i) == i)
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
		{
			s1++;
			l++;
			if (between_quotes(s, l) > l && *s1 != '\0')
			{
				while (between_quotes(s, l) > l && *s1 != '\0')
				{
					l++;
					s1++;
					if (between_quotes(s, l) == l
						&& between_quotes(s, l - 1) > l - 1)
					{
						s1++;
						l++;
					}
				}
			}
			while (*s1 != '\0' && *s1 != c && between_quotes(s, l) == l
				&& (*s1 != '\'' && *s1 != '"'))
			{
				l++;
				s1++;
			}
		}
		while (*s1 != '\0' && *s1 != c && between_quotes(s, l) == l
			&& (*s1 != '\'' && *s1 != '"'))
		{
			l++;
			s1++;
		}
	}
	return (l);
}

char	**write_in(char **tab, char *s, char c)
{
	int		i;
	int		j;
	char	*s2;
	int		max;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	s2 = s;
	max = nb_words(s, c);
	while (*s2 && *s2 != '\0' && i <= max)
	{
		if (*s2 && *s2 != '\0' && (k > 0) && s[k - 1] == c)
			j = 0;
		while (*s2 != '\0' && *s2 != c && (*s2 == '\'' || *s2 == '"'))
		{
			tab[i][j] = *s2;
			s2++;
			k++;
			j++;
			if (between_quotes(s, k) > k && *s2 != '\0')
			{
				while (between_quotes(s, k) > k && *s2 != '\0')
				{
					tab[i][j] = *s2;
					s2++;
					k++;
					j++;
					if (between_quotes(s, k) == k
						&& between_quotes(s, k - 1) > k - 1)
					{
						tab[i][j] = *s2;
						s2++;
						k++;
						j++;
					}
				}
			}
			while (*s2 != '\0' && *s2 != c && between_quotes(s, k) == k
				&& (*s2 != '\'' && *s2 != '"'))
			{
				tab[i][j] = *s2;
				s2++;
				k++;
				j++;
			}
		}
		while (*s2 != '\0' && *s2 != c && between_quotes(s, k) == k
			&& (*s2 != '\'' && *s2 != '"'))
		{
			tab[i][j] = *s2;
			s2++;
			k++;
			j++;
		}
		if (*s2 != '\0' && *s2 == c && j > 0)
		{
			tab[i][j] = '\0';
			i++;
			while (between_quotes(s, k) == k && *s2 == c
				&& *s2 && *s2 != '\0') // PASSE LES ESPACES PAS ENTRE COTES
			{
				s2++;
				k++;
			}
		}
		if ((between_quotes(s, k) == k && *s2 == c && *s2 && *s2 != '\0'))
		{
			s2++;
			k++;
		}
	}
	if (i != max)
		tab[i][j] = '\0';
	tab[max] = NULL;
	return (tab);
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

char	**ft_split_minishell(char	*s, char c)
{
	int			i;
	int			l;
	char		**tab;
	char		*s3;

	i = 0;
	l = 0;
	s3 = s;
	tab = malloc(sizeof(char *) * (nb_words(s, c) + 1));
	if (!tab || s == 0)
	{
		ft_putstr_fd(" ft_split_minishell : malloc failed", 2);
		return (NULL);
	}
	while (*s3)
	{
		while (*s3 == c && *s3 != '\0' && between_quotes(s, l) == l)
		{
			s3++;
			l++;
		}
		if (*s3 != c && *s3 != '\0')
		{
			tab[i] = malloc(sizeof(char) * (size_words(s3, c) + 1));
			if (!tab[i])
			{
				ft_putstr_fd(" ft_split_minishell : malloc failed", 2);
				return (NULL);
			}
			i++;
		}
		while (*s3 != c && *s3 != '\0')
		{	
			while (*s3 && *s3 != '\0' && (*s3 == '\'' || *s3 == '"'))
			{
				s3++;
				l++;
				if (between_quotes(s, l) > l && *s3 != '\0')
				{
					while (between_quotes(s, l) > l && *s3 != '\0')
					{
						l++;
						s3++;
						if (between_quotes(s, l) == l
							&& between_quotes(s, l - 1) > l - 1)
						{
							s3++;
							l++;
						}
					}
				}				
				while (*s3 != '\0' && *s3 != c && between_quotes(s, l) == l
					&& (*s3 != '\'' && *s3 != '"'))
				{
					l++;
					s3++;
				}
			}
			while (*s3 && *s3 != '\0' && *s3 != c && between_quotes(s, l) == l
				&& (*s3 != '\'' && *s3 != '"'))
			{
				l++;
				s3++;
			}
		}	
	}
	return (write_in(tab, s, c));
}
