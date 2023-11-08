/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cleaning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:45:48 by achevala          #+#    #+#             */
/*   Updated: 2023/11/08 14:28:35 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup_checking(char *s, int start, int end)
{
	char	*str;
	int		i;

	i = start;
	str = malloc((end - start) * sizeof(char));
	if (!str)
		return (NULL);
	while (s[i] && i < end)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
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
		return (NULL);
	if (s1)
	{
		while (s1[i] != '\0')
		{
			str[i] = s1[i];
			i++;
		}
	}
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

