/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:50:56 by nap               #+#    #+#             */
/*   Updated: 2023/11/01 16:44:11 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

	
int	between_quotes(char *l, int i)
{
	int		j;

	j = 0;
	while (l[j] && j <= (int)ft_strlen(l) && j < i)
	{
		if (l[j] == '"' || l[j] == '\'') 
		{
            if (check_quotes(l, l[j], j) > i)
				return (check_quotes(l, l[j], j));
			else 
				j = check_quotes(l, l[j], j);
        }
		j++;
	}
	printf("ici %d\n", i);
	return (i);
}
/* between_quotes returns the position of the second quote, after i, 
if l[i] is between quotes, otherwise, it returns i and the char is not
between quotes  */

char	*ft_strdup_section(char *s, int start, int end)
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

