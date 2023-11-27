/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cleaning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:45:48 by achevala          #+#    #+#             */
/*   Updated: 2023/11/27 12:02:57 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

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

char	*my_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (my_strlen(s1) + my_strlen(s2) + 1));
	if (!str)
	{
		ft_putstr_fd("error: create_process: malloc failed", 2);
		return (NULL);
	}
	if (s1)
		str = ft_cpy(str, s1, &i);
	if (s2)
	{
		while (s2[j] != '\0')
		{
			str[i + j] = s2[j];
			j++;
		}
	}
	str[i + j] = '\0';
	return (str);
}

bool	is_ok(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z') || c == '_')
		return (true);
	else
		return (false);
}

void	print_tab(char **tab)
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
