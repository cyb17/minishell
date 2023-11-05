/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cleaning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:45:48 by achevala          #+#    #+#             */
/*   Updated: 2023/11/05 20:53:13 by achevala         ###   ########.fr       */
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0' && i < (int)(ft_strlen(s1) + ft_strlen(s2)))
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}


char	*get_var_to_exp(char *s)
{
	int			i;
	int 		j;
	char		*res;
	char		*s0;

	i = 0;
	j = 0;
	s0 = s;
	while (*s0 >= '0' && *s0 <= '9' || *s0 >= 'A' && *s0 <= 'Z' 
	|| *s0 >= 'a' && *s0 <= 'z' || *s0 == '_')
	{
		s0++;
		i++;
	}
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		return (NULL);
	s0 = s;
	while (j < i)
	{
		res[j] = *s0;
	//	printf("res[j] = %c\n", res[j]);
		j++;
		s0++;
	}
	res[j] = '\0';
	return (res);
}