/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cleaning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:45:48 by achevala          #+#    #+#             */
/*   Updated: 2023/12/22 19:46:57 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

char	*ft_strdup_checking(char *s, int start, int end)
{
	char	*str;
	int		i;

	i = start;
	str = malloc((end - start) * sizeof(char));
	if (!str)
	{
		ft_putstr_fd("error: create_process: malloc failed", 2);
		return (NULL);
	}
	while (s[i] && i < end)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_cpy(char *str, char *s, int *i)
{
	while (s[*i] != '\0')
	{
		str[*i] = s[*i];
		(*i)++;
	}
	return (str);
}

void	my_strjoin_end(char *s2, int i, int *j, char **str)
{
	while (s2[(*j)] != '\0')
	{
		(*str)[i + (*j)] = s2[(*j)];
		(*j)++;
	}
}

char	*my_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (s2 != NULL)
		str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (s2 == NULL)
		str = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!str)
	{
		ft_putstr_fd("error: create_process: malloc failed", 2);
		return (NULL);
	}
	if (s1)
		str = ft_cpy(str, s1, &i);
	if (s2)
		my_strjoin_end(s2, i, &j, &str);
	str[i + j] = '\0';
	return (str);
}

bool	to_delete(char *s, int i)
{
	if (s[i] && s [i + 1] && ((s[i] == '\'' && s[i + 1] == '\'')
			|| (s[i] == '"' && s[i + 1] == '"'))
		&& check_quotes(s, s[i + 1], i + 1) == i + 1
		&& b_q(s, i) == i && b_q(s, i + 1) == i + 1)
		return (true);
	return (false);
}

/* void	print_tab(char **tab)
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
} */
