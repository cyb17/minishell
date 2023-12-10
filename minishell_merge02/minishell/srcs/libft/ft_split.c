/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:09:33 by yachen            #+#    #+#             */
/*   Updated: 2023/08/30 15:52:30 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countword(char const *s, char c)
{
	int	count;
	int	trigger;

	count = 0;
	trigger = 0;
	while (*s)
	{
		if (*s != c && trigger == 0)
		{
			trigger = 1;
			count++;
		}
		else if (*s == c)
			trigger = 0;
		s++;
	}
	return (count);
}

void	ft_free(char **tab, int j)
{
	while (tab[j])
	{
		free(tab[j]);
		j++;
	}
	free(tab);
}

char	**ft_split2(char const*s, char c, char **tab)
{
	size_t	i;
	int		j;
	int		index;

	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			tab[j] = ft_substr(s, index, i - index);
			if (tab[j] == NULL)
				ft_free(tab, j);
			index = -1;
			j++;
		}
		i++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_countword(s, c) + 1));
	if (!s || !tab)
		return (NULL);
	return (ft_split2(s, c, tab));
}
/*
#include <stdio.h>

int	main()
{
//	size_t	i;
	char	**tab = ft_split("      ", ' ');
	
	i = 0;
	while (tab[i])
		{
			printf("%s\n", tab[i]);
			free(tab[i]);
			i++;
		}
	if (tab[0] == NULL)
		printf("oui\n");
	//free(tab);
}*/