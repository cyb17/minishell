/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:48:17 by yachen            #+#    #+#             */
/*   Updated: 2023/05/08 17:47:46 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*ptrs1;
	const unsigned char	*ptrs2;

	i = 0;
	ptrs1 = s1;
	ptrs2 = s2;
	while (i < n)
	{
		if (ptrs1[i] != ptrs2[i])
			return (ptrs1[i] - ptrs2[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	char	s1[] = "chaafjhh";
	char	s2[] = "chaa";
	printf("%d", ft_memcmp(s2, s1, 5));
}*/
