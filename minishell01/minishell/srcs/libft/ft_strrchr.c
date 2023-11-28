/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:59:30 by yachen            #+#    #+#             */
/*   Updated: 2023/05/09 15:59:52 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	i = len + 1;
	while (i--)
	{
		if (s[len] == (char)c)
			return ((char *)s + len);
		len--;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int main()
{
	char str[] = "il fait beau";
	char	*ptr = ft_strrchr(str, '-');
		printf("%p\n", ptr);
		printf("%c", *ptr);
}
*/