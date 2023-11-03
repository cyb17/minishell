/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 20:56:12 by nap               #+#    #+#             */
/*   Updated: 2023/11/01 12:19:03 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	nb_mots(char const *s, char c)
{
	int			m;
	char const	*s0;

	m = 0;
	s0 = s;
	while (*s0 && *s0 != '\0')
	{
		while (*s0 == c && *s0 != '\0')
			s0++;
		if (*s0 != c && *s0 != '\0')
			m++;
		while (*s0 != '\0' && *s0 != c)
			s0++;
	}
	return (m);
}

static int	size_mot(char const *s, char c)
{
	int			l;
	char const	*s1;

	l = 0;
	s1 = s;
	while (*s1 != c && *s1 != '\0')
	{
		l++;
		s1++;
	}
	l++;
	return (l);
}

static char	**write_in(char **tab, char const *s, char c)
{
	int			i;
	int			j;
	char const	*s2;
	int			max;

	i = 0;
	s2 = s;
	max = nb_mots(s, c);
	while (*s2 && *s2 != '\0' && i < max)
	{
		j = 0;
		while (*s2 == c && *s2 != '\0')
			s2++;
		while (*s2 != '\0' && *s2 != c)
		{
			tab[i][j] = *s2;
			j++;
			s2++;
		}
		tab[i][j] = '\0';
		i++;
	}
	tab[i] = 0;
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

char	**ft_split(char const *s, char c)
{
	int			i;
	char		**tab;
	char const	*s3;

	i = 0;
	s3 = s;
	tab = malloc(sizeof(char *) * (nb_mots(s, c) + 1));
	if (!tab || s == 0)
		return (NULL);
	while (*s3)
	{
		while (*s3 == c && *s3 != '\0')
			s3++;
		if (*s3 != c && *s3 != '\0')
		{
			tab[i] = malloc(sizeof(char) * size_mot(s3, c));
			if (!tab[i])
				return (NULL);
			i++;
		}
		while (*s3 != c && *s3 != '\0')
			s3++;
	}
	return (write_in(tab, s, c));
}