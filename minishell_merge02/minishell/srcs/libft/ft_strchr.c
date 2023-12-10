/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:08:32 by yachen            #+#    #+#             */
/*   Updated: 2023/05/09 14:01:47 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	char str[] = "il fait beau";
	char *return_value = ft_strchr(str, 't' + 256);
	if (return_value == NULL)
		printf("NULL");
	else
		printf("%p", return_value);
}
*/