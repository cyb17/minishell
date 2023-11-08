/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:22:59 by achevala          #+#    #+#             */
/*   Updated: 2023/11/07 19:00:48 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		if (between_quotes(s, i) == i && *s0)
		{
			while (*s0 == c && *s0 != '\0')
			{
				s0++;
				i++;
			}
			if (*s0 != c && *s0 != '\0')
				m++;
			while (*s0 != '\0' && *s0 != c)
			{
				s0++;
				i++;
			}
		}
		if (between_quotes(s, i) > i)
		{
			m++;
			while (*s0 != '\0')
			{
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
	if (*s1 == '\'' || *s1 == '"')
	{
		s1++;
		while (between_quotes(s, l) > l && *s1 != '\0')
		{
			l++;
			s1++;
		}
	}
	else 
	{
		while (*s1 != '\0' && *s1 != c && between_quotes(s, l) == l)
		{
			l++;
			s1++;
		}	
	}
	l++;
	return (l);
}

char	**write_in(char **tab, char *s, char c)
{
	int		i;
	int		j;
	char	*s2;
	int		max;

	i = 0;
	s2 = s;
	max = nb_words(s, c);
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

char	**ft_split_minishell(char	*s, char c)
{
	int			i;
	char		**tab;
	char 		*s3;

	i = 0;
	s3 = s;
	tab = malloc(sizeof(char *) * (nb_words(s, c) + 1));
	if (!tab || s == 0)
		return (NULL);
	while (*s3)
	{
		while (*s3 == c && *s3 != '\0')
			s3++;
		if (*s3 != c && *s3 != '\0')
		{
			tab[i] = malloc(sizeof(char) * size_words(s3, c));
			if (!tab[i])
				return (NULL);
			i++;
		}
		while (*s3 != c && *s3 != '\0')
			s3++;
	}
	return (write_in(tab, s, c));
}
// void print_tab(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	if (tab != NULL)
// 	{
// 		while (tab[i])
// 		{
// 			printf("%s -> len = %ld\n", tab[i], strlen(tab[i]));
// 			i++;
// 		}
// 	}
// }
// int	main()
// {
// 	char	*s;
// 	char	c;
// 	char  **res;
// 	int		m;
	
// 	c = ' ';
// 	s =  " echo  pouet '''c''ouc' 'ou'iho ";
// 	m = nb_words(s, c);
// 	res = ft_split_minishell(s, c);
// 	print_tab(res);
// 	printf("nb mots = %d\n", m);
// 	return (0);
// }

/*
s: La chaîne de caractères à découper.
c: Le caractère délimiteur

Valeur de retour:
Le tableau de nouvelles chaînes de caractères
résultant du découpage.
NULL si l’allocation échoue.

Alloue (avec malloc(3)) et retourne un tableau
de chaînes de caractères obtenu en séparant ’s’ à
l’aide du caractère ’c’, utilisé comme délimiteur.
Le tableau doit être terminé par NULL.*/
