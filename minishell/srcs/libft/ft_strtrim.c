/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:45:45 by yachen            #+#    #+#             */
/*   Updated: 2023/05/15 18:39:08 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	start_set_indice(char const	*s1, char const	*set)
{
	size_t	i;

	i = 0;
	while (s1[i] && (ft_strchr(set, s1[i])) != NULL)
		i++;
	return (i);
}

static size_t	end_set_indice(char const	*s1, char const	*set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (i >= 0 && (ft_strchr(set, s1[i])) != NULL)
		i--;
	return (i);
}

char	*ft_strtrim(char const	*s1, char const	*set)
{
	size_t	len;
	char	*str_modif;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	len = end_set_indice(s1, set) - start_set_indice(s1, set) + 2;
	if (start_set_indice(s1, set) == ft_strlen(s1)
		|| end_set_indice(s1, set) == 0)
		return (ft_strdup(""));
	str_modif = (char *)malloc(len * sizeof(char));
	if (str_modif == NULL)
		return (NULL);
	ft_strlcpy(str_modif, s1 + start_set_indice(s1, set), len);
	return (str_modif);
}
/*
#include <stdio.h>

int	main()
{
	char	str[] = "  \n\t\t \t \n";
	char	set[] = "";
	char	*ptr = ft_strtrim(str, set);
	printf("%p\n", ptr);
	printf("%zu\n", ft_strlen(ptr));
	printf("%zu", ft_strlen(str));
	free(ptr);
}
*/