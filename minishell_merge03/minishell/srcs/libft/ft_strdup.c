/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:21:36 by yachen            #+#    #+#             */
/*   Updated: 2023/09/08 12:02:05 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*duplicate_s;
	int		i;

	i = 0;
	duplicate_s = (char *)malloc(sizeof(*duplicate_s) * (ft_strlen(s) + 1));
	if (!duplicate_s)
		return (NULL);
	while (s[i])
	{
		duplicate_s[i] = s[i];
		i++;
	}
	duplicate_s[i] = '\0';
	return (duplicate_s);
}
/*
#include <stdio.h>
#include <string.h>

int	main()
{
	char	*duplicate_s;

	duplicate_s = NULL;
	printf("%p", duplicate_s);
	duplicate_s = strdup("");
	printf("%p", duplicate_s);
	if (*duplicate_s == '\0')
		printf("1");
	free(duplicate_s);
}*/
