/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:24:58 by yachen            #+#    #+#             */
/*   Updated: 2023/05/09 11:07:29 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int main()
{
	char	s1[] = "tripouille";
	char	s2[] = "tripouill";
	printf("%d\n", strncmp(s1, s2, 10));
	printf("%d\n", strncmp(s1, s2, 3));
	printf("%d\n", ft_strncmp(s1, s2, 42));
	printf("%d", strncmp(s1, s2, 42));
}
*/
