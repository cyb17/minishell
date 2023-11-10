/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nap <nap@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:22:59 by achevala          #+#    #+#             */
/*   Updated: 2023/11/10 00:56:35 by nap              ###   ########.fr       */
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
		while (between_quotes(s, i) == i && *s0)
		{
				while (*s0 == c && *s0 != '\0')
				{
					if (between_quotes(s, i) > i)
						break;
					s0++;
					i++;
				}
				if (*s0 != c && *s0 != '\0' 
				&& (between_quotes(s, i - 1) == i - 1))
					m++;
				while (*s0 != '\0' && *s0 != c)
				{
					if (between_quotes(s, i) > i)
						break;
					s0++;
					i++;
				}
		}
		while (between_quotes(s, i) > i)
		{
			//m++;
			while (*s0 != '\0')
			{
				if (between_quotes(s, i) == i)
						break;
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
		l++;
		if (between_quotes(s, l) > l && *s1 != '\0')
		{
			while (between_quotes(s, l) > l && *s1 != '\0')
			{
				l++;
				s1++;
			}
		}
	}
	else
	{
		// if (*s1 != '\0' && *s1 != c && between_quotes(s, l) == l)
		{
			while (*s1 != '\0' && *s1 != c && between_quotes(s, l) == l)
			{
				l++;
				s1++;
			}
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
	int	k;

	i = 0;
	j = 0;
	k = 0;
	s2 = s;
	max = nb_words(s, c);
	while (*s2 && *s2 != '\0' && i <= max)
	{
		while (between_quotes(s, j) == j && *s2 == c && *s2) // PASSE LES ESPACES PAS ENTRE COTES
		{
			if (s[j - 1] != c && s[j - 1])
			{
				tab[i][k] = '\0';
				i++;
				k = 0;
			}
			s2++;
			j++;
			k++;
		}
		while (between_quotes(s, j) > j && *s2) // RECOPIE LES CHARS ENTRE COTE
		{
			tab[i][k] = *s2;
			s2++;
			j++;
			k++;
		}
		while (*s2 != '\0' && *s2 != c && between_quotes(s, j) == j) // RECOPIE LES CHARS PAS ENTRE COTE
		{
			if (between_quotes(s, j) > j)
				break;
			tab[i][k] = *s2;
			s2++;
			j++;
			k++;
		}
		// }
		// while (between_quotes(s, j) > j)
		// {
		// 	//m++;
		// 	while (*s2 != '\0')
		// 	{
		// 		if (between_quotes(s, j) == j)
		// 				break;
		// 		tab[i][j] = *s2;
		// 		s2++;
		// 		j++;
		// 	}
		// }
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
	int			l;
	char		**tab;
	char 		*s3;

	i = 0;
	l = 0;
	s3 = s;
	tab = malloc(sizeof(char *) * (nb_words(s, c) + 1));
	if (!tab || s == 0)
		return (NULL);
	while (*s3)
	{
		while (*s3 == c && *s3 != '\0')
		{
			s3++;
			l++;
		}
		if (*s3 != c && *s3 != '\0')
		{
			tab[i] = malloc(sizeof(char) * size_words(s3, c) + 1);
			if (!tab[i])
				return (NULL);
			i++;
		}
		if (between_quotes(s, l) == l && *s3 != c && *s3 != '\0')
		{
			while (between_quotes(s, l) == l && *s3 != c && *s3 != '\0')
			{
				s3++;
				l++;
			}
		}
		else if (between_quotes(s, l) > l && *s3 != c && *s3 != '\0')
		{
			while (between_quotes(s, l) > l && *s3 != c && *s3 != '\0')
			{
				s3++;
				l++;
			}
		}
	}
	return (write_in(tab, s, c));
}

void print_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i])
		{
			printf("%s -> len = %ld\n", tab[i], strlen(tab[i]));
			i++;
		}
	}
}

int	main(int ac, char **av, char **env)
{
	// char	*s;
	// char	c;
	char  **res;
	int		m;
	char c;
	char 		*input;
	//t_list		*envlist;
	
	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{  
        // envlist = NULL;
	    // envlist = env_to_envlist(env);
		input = readline("minishell > ");
		c = ' ';
		m = nb_words(input, c);
		res = ft_split_minishell(input, c);
		print_tab(res);
		freetab(res);
		printf("nb mots = %d\n", m);
	}
	return (0);
}

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
